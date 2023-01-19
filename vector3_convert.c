/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:04:04 by abossel           #+#    #+#             */
/*   Updated: 2023/01/17 12:36:46 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_v3	irgbtov3(int irgb)
{
	t_v3	colour;

	colour.r = (irgb >> 16) & 0xff;
	colour.g = (irgb >> 8) & 0xff;
	colour.b = irgb & 0xff;
	return (colour);
}

int	v3toirgb(t_v3 vrgb)
{
	vrgb = v3clamp(vrgb, 0.0f, 255.0f);
	return ((int)vrgb.r << 16 | (int)vrgb.g << 8 | (int)vrgb.b);
}
