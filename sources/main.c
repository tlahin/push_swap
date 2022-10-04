/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlahin <tlahin@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:19:16 by tlahin            #+#    #+#             */
/*   Updated: 2022/10/03 13:19:17 by tlahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	free_stuff(t_struct *data, int ret)
{
	if (data->board)
		free_char_array(data->board);
	if (data->heatmap)
		free_int_array(data->heatmap, data);
	return (ret);
}

int init_data(t_struct *data)
{
    ft_bzero(data, sizeof (*data));
    if (player_parser(data) == -1 || parse_size(&data->board_size.row, \
        &data->board_size.col) == -1)
        return (-1);
    data->board = create_char_array(data->board_size.row, \
        data->board_size.col);
    data->heatmap = create_int_array(data);
    if (!data->heatmap || data->board)
        return (-1);
    return (0);
}

int main(void)
{
    t_struct  data;
    int     state;

    state = 1;
    if(init_data(&data) == -1)
        return (free_stuff(&data, -1));
    while (state >= 0)
    {
        if (parse_board(&data) == 0 && parse_piece(&data) == 0)
        {
            update_heatmap(&data);
            state = find_solution(&data);
            free_char_array(data.piece);
        }
        else
            state = -1;
    }
    return (free_stuff(&data, state));
}