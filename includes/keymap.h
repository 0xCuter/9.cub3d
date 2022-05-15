/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scuter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:37:40 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/15 23:36:31 by scuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMAP_H
# define KEYMAP_H

// MOUSE
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

// KEYBOARD
# ifdef __unix__
#  define KEY_ESCAPE	65307
#  define KEY_W			  119
#  define KEY_A			   97
#  define KEY_S			  115
#  define KEY_D			  100
# endif

# ifdef __APPLE__
#  define KEY_ESCAPE	   53
#  define KEY_W			   13
#  define KEY_A			    0
#  define KEY_S			    1
#  define KEY_D			    2
# endif

#endif
