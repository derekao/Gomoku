// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Area.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/03/05 13:09:46 by semartin          #+#    #+#             //
//   Updated: 2018/03/05 13:09:46 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#pragma once

#define BOARD_HEIGHT 19
#define BOARD_WIDTH 19
#define AREA_SIZE 2

#include <iostream>
#include <vector>
#include "Coord.hpp"

class Area
{

public:
	int Width;
	int Height;
	Coord Pos;
	int Density;

	static void Update(std::vector<Area> & PlayArea, int y, int x);

};