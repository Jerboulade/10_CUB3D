/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:52:41 by jcarere           #+#    #+#             */
/*   Updated: 2022/06/12 15:12:17 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*new_link;

	new_link = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_link)
		return (NULL);
	new_link->next = NULL;
	new_link->data = data;
	return (new_link);
}
