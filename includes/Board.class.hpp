// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Board.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/28 11:29:27 by semartin          #+#    #+#             //
//   Updated: 2018/02/28 11:29:27 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "Coord.class.hpp"


class Board
{

private:
	std::vector<int> Content;

public:
	Board();
	~Board();


};