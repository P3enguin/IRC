/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:19:45 by hel-makh          #+#    #+#             */
/*   Updated: 2022/09/01 11:09:26 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/*************************[ Constructors/Destructors ]*************************/

Channel::Channel(std::string _name) {
	if (_name[0] != '#') {
		throw myException("Invalid channel name: must start with '#'.");
	}
	for (std::string::iterator it = _name.begin(); it != _name.end(); ++it) {
		if (isspace(*it)) {
			throw myException("Invalid channel name: contains illegal characters.");
		}
	}
	this->name = _name;
	this->topic = "";
	this->key = "";
	this->membersLimit = 0;
	this->memberChatOnly = true;
	this->inviteOnly = false;
	this->moderated = false;
	this->topicSettable = true;
}

/******************************[ Getters/Setters ]*****************************/

std::string const &	Channel::getName(void) const {
	return (this->name);
}

std::string const &	Channel::getTopic(void) const {
	return (this->topic);
}

std::string const &	Channel::getKey(void) const {
	return (this->key);
}

int	Channel::getMembersLimit(void) const {
	return (this->membersLimit);
}

bool	Channel::isMemberChatOnly(void) const {
	return (this->memberChatOnly);
}

bool	Channel::isInviteOnly(void) const {
	return (this->inviteOnly);
}

bool	Channel::isModerated(void) const {
	return (this->moderated);
}

bool	Channel::isTopicSettable(void) const {
	return (this->topicSettable);
}

std::map <int, User *> &	Channel::getMembers(void) {
	return (this->members);
}

std::vector <int> &	Channel::getOperators(void) {
	return (this->operators);
}

std::vector <int> &	Channel::getModerators(void) {
	return (this->moderators);
}

std::vector <int> &	Channel::getInvitees(void) {
	return (this->invitees);
}

void	Channel::setTopic(std::string _topic, int fd) {
	if (!this->topicSettable && !this->getOperator(fd))
		throw myException("You're not channel operator.");
	this->topic = _topic;
}

void	Channel::setKey(std::string _key, int fd) {
	if (!this->getOperator(fd))
		throw myException("You're not channel operator.");
	this->key = _key;
}

void	Channel::setLimit(int limit, int fd) {
	if (!this->getOperator(fd))
		throw myException("You're not channel operator.");
	this->membersLimit = limit;
}

void	Channel::setMemberChatOnly(bool option, int fd) {
	if (!this->getOperator(fd))
		throw myException("You're not channel operator.");
	this->memberChatOnly = option;
}

void	Channel::setInviteOnly(bool option, int fd) {
	if (!this->getOperator(fd))
		throw myException("You're not channel operator.");
	this->inviteOnly = option;
}

void	Channel::setModerated(bool option, int fd) {
	if (!this->getOperator(fd))
		throw myException("You're not channel operator.");
	this->moderated = option;
}

void	Channel::setTopicSettable(bool option, int fd) {
	if (!this->getOperator(fd))
		throw myException("You're not channel operator.");
	this->topicSettable = option;
}

/*****************************[ Member Functions ]*****************************/

User *	Channel::getMember(int fd) {
	std::map<int, User *>::iterator	it;

	it = this->members.find(fd);
	if (it != this->members.end())
		return (it->second);
	return (NULL);
}

User *	Channel::getOperator(int fd) {
	std::vector<int>::iterator	it;

	it = std::find(this->operators.begin(), this->operators.end(), fd);
	if (it != this->operators.end())
		return (this->getMember(fd));
	return (NULL);
}

User *	Channel::getModerator(int fd) {
	std::vector<int>::iterator	it;

	it = std::find(this->moderators.begin(), this->moderators.end(), fd);
	if (it != this->moderators.end())
		return (this->getMember(fd));
	return (NULL);
}

User *	Channel::getInvitee(int fd) {
	std::vector<int>::iterator	it;

	it = std::find(this->invitees.begin(), this->invitees.end(), fd);
	if (it != this->invitees.end())
		return (this->getMember(fd));
	return (NULL);
}

void	Channel::addOperator(int fd) {
	User *	member;
	
	member = this->getMember(fd);
	if (member == NULL) {
		throw myException("Invalid username: user not in channel.");
	}
	this->operators.push_back(fd);
}

void	Channel::removeOperator(int fd) {
	User *						member;
	std::vector<int>::iterator	it;
	
	member = this->getMember(fd);
	if (member == NULL) {
		throw myException("Invalid username: user not in channel.");
	}
	it = std::find(this->operators.begin(), this->operators.end(), fd);
	if (it == this->operators.end()) {
		throw myException("User is not an operator.");
	}
	this->operators.erase(it);
}

void	Channel::addModerator(int fd) {
	User *	member;
	
	member = this->getMember(fd);
	if (member == NULL) {
		throw myException("Invalid username: user not in channel.");
	}
	this->moderators.push_back(fd);
}

void	Channel::removeModerator(int fd) {
	User *						member;
	std::vector<int>::iterator	it;
	
	member = this->getMember(fd);
	if (member == NULL) {
		throw myException("Invalid username: user not in channel.");
	}
	it = std::find(this->moderators.begin(), this->moderators.end(), fd);
	if (it == this->moderators.end()) {
		throw myException("User is not a moderator.");
	}
	this->moderators.erase(it);
}

void	Channel::addInvitee(int fd) {
	User *	member;
	
	member = this->getMember(fd);
	if (member == NULL) {
		throw myException("Invalid username: user not in channel.");
	}
	this->invitees.push_back(fd);
}

void	Channel::removeInvitee(int fd) {
	User *						member;
	std::vector<int>::iterator	it;
	
	member = this->getMember(fd);
	if (member == NULL) {
		throw myException("Invalid username: user not in channel.");
	}
	it = std::find(this->invitees.begin(), this->invitees.end(), fd);
	if (it == this->invitees.end()) {
		throw myException("User is not a moderator.");
	}
	this->invitees.erase(it);
}

void	Channel::addMember(User * member, std::string key) {
	if (this->inviteOnly && !this->getInvitee(member->getFd())) {
		throw myException("User is not invited.");
	}
	if (!this->key.empty() && this->key != key) {
		throw myException("Invalid channel key.");
	}
	if (this->members.insert(std::pair<int, User *>(member->getFd(), member)).second) {
		member->joinChannel(*this, this->name);
		if (this->members.size() == 1) {
			this->addOperator(member->getFd());
		}
		if (this->inviteOnly && this->getInvitee(member->getFd())) {
			this->removeInvitee(member->getFd());
		}
	}
}

void	Channel::removeMember(int fd) {
	try {
		std::map<int, User *>::iterator	it;

		it = this->members.find(fd);
		if (it != this->members.end()) {
			this->removeOperator(fd);
			this->removeModerator(fd);
			this->removeInvitee(fd);
			it->second->leaveChannel(this->name);
			this->members.erase(it);
		}
	} catch (std::exception & e) {
		throw myException(std::string(e.what()));
	}
}

void	Channel::broadCastMessage(std::string & message, int fd) {
	std::map<int, User *>::iterator	it;

	if (this->memberChatOnly && !this->getMember(fd)) {
		throw myException("Cannot send to channel.");
	}
	if (fd != -1 && this->moderated && !this->getModerator(fd)) {
		throw myException("Cannot send to moderated channel.");
	}
	for (it = this->members.begin(); it != this->members.end(); ++it) {
		send(it->second->getFd(), message.c_str(), sizeof(message.c_str()), 0);
	}
}
