#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
std::shared_ptr<Storage> Storage::m_instance = nullptr;

bool Storage::readFromFile() {
	ifstream file;
	ifstream filei;
	file.open(Path::userPath, ios::in);
	filei.open(Path::meetingPath, ios::in);
	if (!(file.is_open() && filei.is_open())) {
		return false;
	}
	string s[100];
	string l, n;
	while (std::getline(file, l)) {
		istringstream is(l);
		int j = 0;
		while (std::getline(is, n, ',')) {
			string x = n.substr(1, n.length()-2);
			s[j] = x;
			j++;
			if (j == 4)  break;
		}
		m_userList.push_back(User(s[0], s[1], s[2], s[3]));
	}
	file.close();

	string q[100];
	string li, ni;
	while (std::getline(filei, li)) {
		istringstream isi(li);
		int ji = 0;
		std::vector<std::string> t;
		while (std::getline(isi, ni, ',')) {
			q[ji] = ni.substr(1, ni.length()-2);
			if (ji == 1) {
				int w = 0;
				std::string temp = "";
				while (w != q[1].length()) {
					if (q[1][w] != '&') {
						temp += q[1][w];
					} else {
						t.push_back(temp);
						temp = "";
					}
					w++;
				}
				t.push_back(temp);
			}
			ji++;
			if (ji == 5)  break;
		}
		m_meetingList.push_back(Meeting(q[0], t, q[2], q[3], q[4]));
	}
	filei.close();
	return true;
}
bool Storage::writeToFile() {
	ofstream file_user;
	ofstream file_meeting;
	file_user.open(Path::userPath, ios::out);
	file_meeting.open(Path::meetingPath, ios::out);
	if (!(file_user.is_open() && file_meeting.is_open())) {
		return false;
	}
	auto it = m_userList.begin();
	for (; it != m_userList.end(); it++) {
		file_user << '\"' << it->getName() << '\"' << ',' << '\"' << it->getPassword() << '\"'
		<< ',' << '\"' << it->getEmail() << '\"' << ',' << '\"' << it->getPhone() << '\"' << '\n';
	}
	file_user.close();
	auto it_ = m_meetingList.begin();
	for (; it_ != m_meetingList.end(); it_++) {
		file_meeting << '\"' << it_->getSponsor() << '\"' << ',';
		std::vector<string> temp = it_->getParticipator();
		auto pp = temp.begin();
		file_meeting << '\"' << *pp;
		for (pp++; pp != temp.end(); pp++) {
			file_meeting << '&' << *pp;
		}
		file_meeting << '\"' << ',' << '\"' << Date::dateToString(it_->getStartDate()) << '\"' << ',' << '\"'
		<< Date::dateToString(it_->getEndDate()) << '\"' << ',' << '\"' << it_->getTitle() << '\"' << '\n';
	}
	file_meeting.close();
	return true;
}

Storage::Storage() {
	readFromFile();
	m_dirty = false;
}
std::shared_ptr<Storage> Storage::getInstance(void) {
	if (m_instance == nullptr)
		m_instance.reset(new Storage());
	return m_instance;
}

Storage::~Storage() {
	sync();
}
void Storage::createUser(const User & t_user) {
	m_userList.push_back(t_user);
	m_dirty = true;
	sync();
}
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
	std::list<User> temp;
	auto it = m_userList.begin();
	for (; it != m_userList.end(); it++) {
		if (filter(*it)) {
			temp.push_back(*it);
		}
	}
	return temp;
}
int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
	int n = 0;
	std::list<User>::iterator it;
	for (it = m_userList.begin(); it != m_userList.end(); it++) {
		if (filter(*it)) {
			switcher(*it);
			n++;
		}
	}
	if (n != 0) {
		m_dirty = true;
		sync();
	}
	return n;
}
int Storage::deleteUser(std::function<bool(const User &)> filter) {
	int n = 0;
	std::list<User>::iterator it = m_userList.begin();
	while (it != m_userList.end()) {
		if (filter(*it)) {
			it = m_userList.erase(it);
			n++;
		} else {
			it++;
		}
	}
	m_dirty = true;
	sync();
	return n;
}
void Storage::createMeeting(const Meeting & t_meeting) {
	m_meetingList.push_back(t_meeting);
	m_dirty = true;
	sync();
}
std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
	std::list<Meeting> temp;
	auto it = m_meetingList.begin();
	for (; it != m_meetingList.end(); it++) {
		if (filter(*it)) {
			temp.push_back(*it);
		}
	}
	return temp;
}
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
	int n = 0;
	std::list<Meeting>::iterator it;
	for (it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
		if (filter(*it)) {
			switcher(*it);
			n++;
		}
	}
	if (n != 0) {
		m_dirty = true;
	}
	sync();
	return n;
}
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
	int n = 0;
	std::list<Meeting>::iterator it = m_meetingList.begin();
	while (it != m_meetingList.end()) {
		if (filter(*it)) {
			it = m_meetingList.erase(it);
			n++;
		} else {
			it++;
		}
	}
	m_dirty = true;
	sync();
	return n;
}
bool Storage::sync(void) {
	if (m_dirty) {
		writeToFile();
		m_dirty = false;
		return !m_dirty;
    }
    return false;
}
