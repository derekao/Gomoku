// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Coord.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/02/22 14:22:05 by semartin          #+#    #+#             //
//   Updated: 2018/02/22 14:22:09 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>

class Coord
{

public:
	Coord(int _y, int _x) : y(_y), x(_x){} ; 
	Coord(){};
	int y;
	int x;

	void set(int _y, int _x) { y = _y; x = _x; };

};