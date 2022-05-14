/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:37:40 by vvandenb          #+#    #+#             */
/*   Updated: 2022/05/11 14:37:41 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMAP_H
# define KEYMAP_H

// MOUSE
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

// KEYBOARD
# ifdef __unix__
#  define KEY_ESCAPE 65307
# endif

# ifdef __APPLE__
#  define KEY_ESCAPE 53
# endif

#endif
