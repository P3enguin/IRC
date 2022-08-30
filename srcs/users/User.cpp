/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:25:31 by mbabela           #+#    #+#             */
/*   Updated: 2022/08/30 16:16:57 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "User.hpp"

/*************************[ Constructors/Destructors ]*************************/

User::User(int _fd)
{
	this->fd			= _fd;
	this->username		= "";
	this->nickname		= "";
	this->password		= "";
	this->servername 	= "";
	this->fullName	 	= "";
	this->hostname   	= "";
}

User::~User()
{
	close(this->fd);
}

/******************************[ Getters/Setters ]*****************************/

int	User::getFd(void) const {
	return (this->fd);
}

std::string const &	User::getUsername(void) const {
	return (this->username);
}

std::string	const &	User::getNickname(void) const {
	return (this->nickname);
}

std::string	const &	User::getPassword(void) const {
	return (this->password);
}

std::string const & User::getServerName(void) const
{
	return (this->servername);
}

std::string const & User::getHostName(void) const
{
	return (this->hostname);
}

std::string const & User::getFullName(void) const
{
	return (this->fullName);
}

std::map<std::string, Channel *> &	User::getChannels(void) {
	return (this->channels);
}

Channel *	User::getChannel(std::string name) {
	std::map<std::string, Channel *>::iterator it;

	it = this->channels.find(name);
	if (it != this->channels.end()) {
		return (it->second);
	}
	return (NULL);
}

void	User::setFd(int _fd) {
	this->fd = _fd;
}

void	User::setUsername(std::string _username) {
	this->username = _username;
}

void	User::setNickname(std::string _nickname) {
	this->nickname = _nickname;
}

void	User::setPassword(std::string _password) {
	this->password = _password;
}

void	User::setServerName(std::string servername)
{
	this->servername = servername;
}

void	User::setHostName(std::string hostname)
{
	this->hostname = hostname;
}

void	User::setFullName(std::string fullName)
{
	this->fullName = fullName;
}

/*****************************[ Member Functions ]*****************************/

bool	User::isAuth(void)
{
	return (!this->username.empty()
		&& !this->nickname.empty()
		&& !this->password.empty());
}

void	User::joinChannel(Channel & _channel) {
	this->channels.insert(std::pair<std::string, Channel *>(_channel.getName(), &_channel));
	_channel.addMember(this, this->username);
}

void	User::leaveChannel(std::string name) {
	std::map<std::string, Channel *>::iterator it;

	it = this->channels.find(name);
	if (it == this->channels.end()) {
		throw notInChannel();
	}
	it->second->removeMember(this->username);
	this->channels.erase(it);
}
