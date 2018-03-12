#include "AgendaService.hpp"
#include <iostream>
  //  std::shared_ptr<Storage> m_storage
AgendaService::AgendaService() {
	startAgenda();
}
AgendaService::~AgendaService() {
	quitAgenda();
}
bool AgendaService::userLogIn(const std::string userName, const std::string password) {
	auto filter = [=](const User & u) -> bool {
		if (u.getName() == userName && u.getPassword() == password) {
			return true;
		} else {
			return false;
		}
	};
    std::list<User> temp = m_storage->queryUser(filter);
    if (temp.empty()) {
    	return false;
    } else {
    	return true;
    }
}

bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
	auto filter = [=](const User & temp) -> bool {
		if (temp.getName() == userName)
			return true;
		else
			return false;
	};
	std::list<User> u = m_storage->queryUser(filter);
	if (!u.empty()) {
		return false;
	} else {
		m_storage->createUser(User(userName, password, email, phone));
		return true;
	}
}
bool AgendaService::deleteUser(const std::string userName, const std::string password) {
	auto filter = [=](const User & u) -> bool {
		if (u.getName() == userName && u.getPassword() == password) {
			return true;
		} else {
			return false;
		}
	};
	auto f = [=](const Meeting & m) -> bool {
		if ((m.getSponsor() == userName) || (m.isParticipator(userName))) {
			return true;
		}
		return false;
	};
    int i = m_storage->deleteUser(filter);
    if (i != 0) {  //
    	m_storage->deleteMeeting(f);
    	return true;
    }
    return false;
}
std::list<User> AgendaService::listAllUsers(void) const {
	auto filter = [=](const User & u) -> bool {
		return true;
	};
	return m_storage->queryUser(filter);
}
bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) {
	std::vector<std::string> again = participator;
	again.push_back(userName);
	for (int i = 0; i < again.size()-1; i++) {
		for (int j = i+1; j < again.size(); j++) {
			if (again[i] == again[j])
				return false;
		}
	}
	auto fi = [=](const Meeting& temp1) -> bool {
		return true;
	};
	std::list<Meeting> t = m_storage->queryMeeting(fi);
	auto it_ = t.begin();
	for (; it_ != t.end(); it_++) {
		if (it_->getTitle() == title)
			return false;
	}
	auto h = [=](const User& temp) -> bool {
		if (temp.getName() == userName)
			return true;
		for (int j = 0; j < participator.size(); j++) {
			if (temp.getName() == participator[j])
				return true;
		}
		return false;
	};
	std::list<User> u = m_storage->queryUser(h);
	int siz;
	siz = 1+participator.size();
	if (u.size() != siz)
		return false;
	if (participator.size() == 0)
		return false;
	Date s(startDate);
	Date e(endDate);
	if (s.getYear() == 0 || e.getYear() == 0) {
		return false;
	}
	if (s >= e)
		return false;
	auto filter = [=](const Meeting & meet) -> bool {
		if (meet.getSponsor() == userName) {
			return true;
		}
		std::vector<std::string> p = meet.getParticipator();
		for (int j = 0; j < p.size(); j++) {
			if (userName == p[j])
				return true;
		}
		for (int i = 0; i < participator.size(); i++) {
			if (meet.getSponsor() == participator[i]) {
				return true;
		    }
			for (int k = 0; k < p.size(); k++) {
				if (participator[i] == p[k])
					return true;
			}
		}
		return false;
	};
	std::list<Meeting> me = m_storage->queryMeeting(filter);
	auto it = me.begin();
	for (; it != me.end(); it++) {
		if ((it->getStartDate() < s && it->getEndDate() <= s) || (it->getStartDate() >= e && it->getEndDate() > e)) {
			continue;
		} else {
			return false;
		}
	}
	Meeting m(userName, participator, startDate, endDate, title);
	m_storage->createMeeting(m);
	return true;
}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
	auto f = [=](const Meeting & m) -> bool {
		if ((m.getSponsor() == userName || m.isParticipator(userName)) && m.getTitle() == title) {
			return true;
		}
		return false;
	};
	std::list<Meeting> me = m_storage->queryMeeting(f);
	return me;
}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
	Date s(startDate);
	Date e(endDate);
	if ((s.getYear() == 0 || e.getYear() == 0) || (s > e)) {
		std::list<Meeting> kong;
		return kong;
	}
	auto f = [=](const Meeting & m) -> bool {
		if (m.getSponsor() == userName || m.isParticipator(userName)) {
			if ((m.getStartDate() <= s && m.getEndDate() >= s) || (m.getStartDate() >= s && m.getStartDate() <= e)) {
				return true;
			}
		}
		return false;
	};
	std::list<Meeting> me = m_storage->queryMeeting(f);
	return me;
}
std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
	auto f = [=](const Meeting & m) -> bool {
		if (m.getSponsor() == userName || m.isParticipator(userName)) {
			return true;
		}
		return false;
	};
	std::list<Meeting> me = m_storage->queryMeeting(f);
	return me;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
	auto f = [=](const Meeting & m) -> bool {
		if (m.getSponsor() == userName) {
			return true;
		}
		return false;
	};
	std::list<Meeting> me = m_storage->queryMeeting(f);
	return me;
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
	auto f = [=](const Meeting & m) -> bool {
		if (m.isParticipator(userName) && m.getSponsor() != userName) {
			return true;
		}
		return false;
	};
	std::list<Meeting> me = m_storage->queryMeeting(f);
	return me;
}
bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
	auto f = [=](const Meeting & m) -> bool {
		if (m.getSponsor() == userName && title == m.getTitle()) {
			return true;
		}
		return false;
	};
    return m_storage->deleteMeeting(f);
}
bool AgendaService::deleteAllMeetings(const std::string userName) {
	auto f = [=](const Meeting & m) -> bool {
		if (m.getSponsor() == userName) {
			return true;
		}
		return false;
	};
    return m_storage->deleteMeeting(f);
}

void AgendaService::startAgenda(void) {
	m_storage = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
	m_storage.reset();
}
