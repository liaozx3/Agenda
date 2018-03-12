#include "AgendaUI.hpp"
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

bool haha = false;
AgendaUI::AgendaUI():m_agendaService() {
	m_userName = "";
	m_userPassword = "";
}
void AgendaUI::OperationLoop(void) {
	startAgenda();
	while (1) {
		if (m_userName.length() == 0) {
			cout << "----------------------------Agenda------------------------------------" << endl;
			cout << "Action :" << endl;
			cout << "l    - log in Agenda by user name and password" << endl;
			cout << "r    - register an Agenda account" << endl;
			cout << "q    - quit Agenda" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << endl;
			cout << "Agenda : ~$ ";
		} else {
			cout << "----------------------------Agenda------------------------------------" << endl;
			cout << "Action :" << endl;
			cout << "o    - log out Agenda" << endl;
			cout << "dc   - delete Agenda account" << endl;
			cout << "lu   - list all Agenda user" << endl;
			cout << "cm   - create a meeting" << endl;
			cout << "la   - list all meetings" << endl;
			cout << "las  - list all sponsor meetings" << endl;
			cout << "lap  - list all participate meetings" << endl;
			cout << "qm   - query meeting by title" << endl;
			cout << "qt   - query meeting by time interval" << endl;
			cout << "dm   - delete meeting by title" << endl;
			cout << "da   - dalete all meetings" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << endl;
			cout << "Agenda@" << m_userName << " : # ";
		}
		std::string get = getOperation();
		bool flag = executeOperation(get);
		if (!flag)
			cout << "error input" << endl;
		if (get == "q") {
			if (!(haha)) {
				quitAgenda();
				break;
			}
		}
	}
}

void AgendaUI::startAgenda(void) {
	m_agendaService.startAgenda();
}
std::string AgendaUI::getOperation() {
	std::string s;
	cin >> s;
	return s;
}
bool AgendaUI::executeOperation(std::string t_operation) {
	if (t_operation == "l") {
		if (haha) {
			return false;
		}
		userLogIn();
		return true;
	}
	if (t_operation == "r") {
		if (haha) {
			return false;
		}
		userRegister();
		return true;
	}
	if (t_operation == "q") {
		if (haha) {
			return false;
		}
		quitAgenda();
		return true;
	}
	if (t_operation == "o") {
		if (!(haha)) {
			return false;
		}
		userLogOut();
		return true;
	}
	if (t_operation == "dc") {
		if (!(haha)) {
			return false;
		}
		deleteUser();
		return true;
	}
	if (t_operation == "lu") {
		if (!(haha)) {
			return false;
		}
		listAllUsers();
		return true;
	}
	if (t_operation == "cm") {
		if (!(haha)) {
			return false;
		}
		createMeeting();
		return true;
	}
	if (t_operation == "la") {
		if (!(haha)) {
			return false;
		}
		listAllMeetings();
		return true;
	}
	if (t_operation == "las") {
		if (!(haha)) {
			return false;
		}
		listAllSponsorMeetings();
		return true;
	}
	if (t_operation == "lap") {
		if (!(haha)) {
			return false;
		}
		listAllParticipateMeetings();
		return true;
	}
	if (t_operation == "qm") {
		if (!(haha)) {
			return false;
		}
		queryMeetingByTitle();
		return true;
	}
	if (t_operation == "qt") {
		if (!(haha)) {
			return false;
		}
		queryMeetingByTimeInterval();
		return true;
	}
	if (t_operation == "dm") {
		if (!(haha)) {
			return false;
		}
		deleteMeetingByTitle();
		return true;
	}
	if (t_operation == "da") {
		if (!(haha)) {
			return false;
		}
		deleteAllMeetings();
		return true;
	}
	return false;
}
void AgendaUI::userLogIn(void) {
	cout << endl;
	cout << "[log in] [user name] [password]" << endl;
	cout << "[log in] ";
	string n, p;
	cin >> n >> p;
	bool flag = m_agendaService.userLogIn(n, p);
	if (flag) {
		m_userName = n;
		m_userPassword = p;
		cout << "[log in] succeed!" << endl;
		haha = true;
	} else {
		cout << "[error] log in fail!" << endl;
	}
}
void AgendaUI::userRegister(void) {
	cout << endl;
	cout << "[register] [user name] [password] [email] [phone]" << endl;
	cout << "[register] ";
	string n, p, e, ph;
	cin >> n >> p >> e >> ph;
	bool flag = m_agendaService.userRegister(n, p, e, ph);
	if (flag) {
		cout << "[register] succeed!" << endl;
	} else {
		cout << "[error] register fail!" << endl;
	}
}
void AgendaUI::quitAgenda(void) {
	m_agendaService.quitAgenda();
}
void AgendaUI::userLogOut(void) {
	haha = false;
	m_userName = "";
	m_userPassword = "";
}
void AgendaUI::deleteUser(void) {
	bool flag = m_agendaService.deleteUser(m_userName, m_userPassword);
	if (flag) {
		haha = false;
		cout << "[delete agenda account] succeed!" << endl;
		m_userName = "";
		m_userPassword = "";
	}
	else
	cout << "[delete agenda account] fail!" << endl;
}
void AgendaUI::listAllUsers(void) {
	cout << endl;
	cout << "[list all users] " << endl << endl;
	std::list<User> u = m_agendaService.listAllUsers();
	cout << left;
	cout << setw(20) << "name" << setw(20) << "email" << setw(20) << "phone" << endl;
	auto it = u.begin();
	for (; it != u.end(); it++) {
		cout << setw(20) << it->getName() << setw(20) << it->getEmail() << setw(20) << it->getPhone() << endl;
	}
}
int change(string s) {
    stringstream ss(s);
    int temp;
    ss >> temp;
    return temp;
}
void AgendaUI::createMeeting(void) {
	cout << endl;
	int count;
	std::string t, s, e;
	std::vector<std::string> pl;
	cout << "[create meeting] [the number of participators]" << endl;
	cout << "[create meeting] ";
	std::string s_count;
	cin >> s_count;
	for (int j = 0; j < s_count.size(); j++) {
		if (s_count[j] < '0' || s_count[j] > '9') {
			cout << "[create meeting] error!" << endl;
			return;
		}
	}
	count = change(s_count);
	for (int i = 1; i <= count; i++) {
		cout << "[create meeting] [please enter the participator " << i << " ]" << endl;
		cout << "[create meeting] ";
		std::string p;
		cin >> p;
		pl.push_back(p);
	}
	cout << "[create meeting] [title][start time(yyyy-mm-dd/hh:mm)][end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[create meeting] ";
	cin >> t >> s >> e;
	bool flag = m_agendaService.createMeeting(m_userName, t, s, e, pl);
	if (count <= 0)
		flag = false;
	if (flag)
		cout << "[create meeting] succeed!" << endl;
	else
		cout << "[create meeting] error!" << endl;
}
void AgendaUI::listAllMeetings(void) {
	cout << endl;
	cout << "[list all meetings]" << endl << endl;
	cout << left;
	cout << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time"
	<< setw(20) << "end time" << setw(20) << "participators" <<endl;
	std::list<Meeting> m = m_agendaService.listAllMeetings(m_userName);
	printMeetings(m);
}
void AgendaUI::listAllSponsorMeetings(void) {
	cout << endl;
	cout << "[list all sponsor meetings]" << endl << endl;
	cout << left;
	cout << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time"
	<< setw(20) << "end time" << setw(20) << "participators" <<endl;
	std::list<Meeting> m = m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(m);
}
void AgendaUI::listAllParticipateMeetings(void) {
	cout << endl;
	cout << "[list all participator meetings]" << endl << endl;
	cout << left;
	cout << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time"
	<< setw(20) << "end time" << setw(20) << "participators" <<endl;
	std::list<Meeting> m = m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(m);
}
void AgendaUI::queryMeetingByTitle(void) {
	cout << "[query meeting] [title]" << endl;
	cout << "[query meeting] ";
	std::string t;
	cin >> t;
	std::list<Meeting> m = m_agendaService.meetingQuery(m_userName, t);
	cout << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time"
	<< setw(20) << "end time" << setw(20) << "participators" <<endl;
	printMeetings(m);
}
void AgendaUI::queryMeetingByTimeInterval(void) {
	cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)][end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[query meeting] ";
	std::string s, e;
	cin >> s >> e;
	cout << "[query meeting]" << endl << endl;
	cout << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time"
	<< setw(20) << "end time" << setw(20) << "participators" <<endl;
	std::list<Meeting> m = m_agendaService.meetingQuery(m_userName, s, e);
	printMeetings(m);
}
void AgendaUI::deleteMeetingByTitle(void) {
	cout << endl;
	cout << "[delete meeting] [title]" << endl;
	cout << "[delete meeting] ";
	std::string t;
	cin >> t;
	bool flag = m_agendaService.deleteMeeting(m_userName, t);
	if (flag)
		cout << "[delete meeting by title] succeed!" << endl;
	else
		cout << "[error] delete meeting fail!" << endl;
}
void AgendaUI::deleteAllMeetings(void) {
	cout << endl;
	bool flag = m_agendaService.deleteAllMeetings(m_userName);
	if (flag)
		cout << "[delete all meeting] succeed!" << endl;
	else
		cout << "[error] delete all meeting fail!" << endl;
}
void AgendaUI::printMeetings(std::list<Meeting> m) {
	auto it = m.begin();
	for (; it != m.end(); it++) {
		std::vector<std::string> par = it->getParticipator();
		std::string p;
		for (int i = 0; i < par.size()-1; i++) {
			p += par[i];
			p += ",";
		}
		p += par[par.size()-1];
		cout << setw(20) << it->getTitle() << setw(20) << it->getSponsor() << setw(20)
		<< Date::dateToString(it->getStartDate()) << setw(20)
		<< Date::dateToString(it->getEndDate()) << setw(20) << p << endl;
	}
}

