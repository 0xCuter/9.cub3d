/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:37:40 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/17 17:39:16 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMAP_H
# define KEYMAP_H

//KEYBOARD
# ifdef __unix__
#  define KEY_ESCAPE	65307
#  define KEY_W			119
#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_LEFT		65361
#  define KEY_RIGHT		65363
# endif

# ifdef __APPLE__
#  define KEY_ESCAPE	53
#  define KEY_W			13
#  define KEY_A			0
#  define KEY_S			1
#  define KEY_D			2
#  define KEY_LEFT		123
#  define KEY_RIGHT		124
# endif

#endif
