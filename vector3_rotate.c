/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 00:26:15 by abossel           #+#    #+#             */
/*   Updated: 2023/01/05 10:44:57 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>

/*
 * rotate on the x axis
 * x2 = x
 * y2 = y * cos(a) - z * sin(a)
 * z2 = y * sin(a) + z * cos(a)
 */
t_v3	v3rotx(t_v3 vector, float radians)
{
	t_v3	vector2;
	float	cos_radians;
	float	sin_radians;

	if (radians == 0.0f)
		return (vector);
	cos_radians = cos(radians);
	sin_radians = sin(radians);
	vector2.v[0] = vector.v[0];
	vector2.v[1] = vector.v[1] * cos_radians - vector.v[2] * sin_radians;
	vector2.v[2] = vector.v[1] * sin_radians + vector.v[2] * cos_radians;
	return (vector2);
}

/*
 * rotate on the y axis
 * x2 = x * cos(a) + z * sin(a)
 * y2 = y
 * z2 = z * cos(a) - x * sin(a)
 */
t_v3	v3roty(t_v3 vector, float radians)
{
	t_v3	vector2;
	float	cos_radians;
	float	sin_radians;

	if (radians == 0.0f)
		return (vector);
	cos_radians = cos(radians);
	sin_radians = sin(radians);
	vector2.v[0] = vector.v[0] * cos_radians + vector.v[2] * sin_radians;
	vector2.v[1] = vector.v[1];
	vector2.v[2] = vector.v[2] * cos_radians - vector.v[0] * sin_radians;
	return (vector2);
}

/*
 * rotate on the z axis
 * x2 = x * cos(a) - y * sin(a)
 * y2 = x * sin(a) + y * cos(a)
 * z2 = z
 */
t_v3	v3rotz(t_v3 vector, float radians)
{
	t_v3	vector2;
	float	cos_radians;
	float	sin_radians;

	if (radians == 0.0f)
		return (vector);
	cos_radians = cos(radians);
	sin_radians = sin(radians);
	vector2.v[0] = vector.v[0] * cos_radians - vector.v[1] * sin_radians;
	vector2.v[1] = vector.v[0] * sin_radians + vector.v[1] * cos_radians;
	vector2.v[2] = vector.v[2];
	return (vector2);
}

/*
 * rotate on an axis using Rodrigues' rotation formula
 * vr = v * cos(a) + (k x v) * sin(a) + k * (k . v) * (1 - cos(a))
 * v is the vector to rotate
 * k is the normalised rotation axis
 * a in the rotation angle
 */
t_v3	v3rot_axis(t_v3 vector, t_v3 axis, float radians)
{
	t_v3	rotate;
	float	cos_radians;
	float	scale;

	if (radians == 0.0f)
		return (vector);
	cos_radians = cos(radians);
	rotate = v3scale(vector, cos_radians);
	rotate = v3add(rotate, v3scale(v3cross(axis, vector), sin(radians)));
	scale = v3dot(axis, vector) * (1.0f - cos_radians);
	rotate = v3add(rotate, v3scale(axis, scale));
	return (rotate);
}

/*
 * rotate a vector to dst direction relative to src direction
 */
t_v3    v3rot_rel(t_v3 vector, t_v3 src_direction, t_v3 dst_direction)
{
    t_v3    axis;
    float   angle;

	axis = v3norm(v3cross(src_direction, dst_direction));
	angle = acos(v3dot(src_direction, dst_direction));
    return (v3rot_axis(vector, axis, angle));
}
