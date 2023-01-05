/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:13:23 by suchua            #+#    #+#             */
/*   Updated: 2022/11/07 19:23:37 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *src)
{
	char	*duplicate;
	int		i;

	duplicate = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	i = -1;
	while (src[++i])
		duplicate[i] = src[i];
	duplicate[i] = '\0';
	return (duplicate);
}
