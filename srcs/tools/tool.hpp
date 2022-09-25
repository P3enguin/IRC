/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabela <mbabela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:28:22 by mbabela           #+#    #+#             */
/*   Updated: 2022/09/25 12:20:36 by mbabela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_HPP
# define TOOL_HPP

# include <iostream>
# include <ostream>
# include <cstddef>
# include <string>
# include <sstream>
# include <vector>
# include <sys/socket.h>
# include <stdarg.h>
# include "replies.hpp"

class myException : public std::exception {
	private:
		std::string	message;
		int			err_numb;	

	public:
		myException(std::string msg) : message(msg) {}
		myException(int err_no) : message(err_reply(err_no)), err_numb(err_no) {}
		virtual ~myException() throw() {}
		
		char const *	what() const throw() {
			return (message.c_str());
		}
		int				getERROR_NO()
		{
			return (err_numb);
		}
};

bool				isNumeric(std::string const &str);
void				split(std::string const &s1, char delim, std::vector<std::string> &out);
int					paramsChecker(const std::string &param);

std::string const	ft_tostring(int n);
int					ft_toInt(std::string const & str);
std::string const	stringBuilder(int n, ...);
void				sendReply(int fd, const std::string &reply);

//void	sendReply(int fd,const std::string &replay);
#endif