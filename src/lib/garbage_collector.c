/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:41:49 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:35:44 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Mémo usage (allocs auto gérées) :
**
**	memory_init() → crée la structure
**	memory_add(mem, ptr) → ajoute un pointeur
**	memory_remove_one(mem, ptr) → libère un seul
**	memory_cleanup(mem) → tout libérer
**	memory_debug_display(mem) → affiche les blocs (debug)
*/

/*
** Crée le gestionnaire mémoire (liste vide)
*/
t_memory	*memory_init(void)
{
	t_memory	*mem;

	mem = malloc(sizeof(t_memory));
	if (!mem)
		return (NULL);
	mem->head = NULL;
	return (mem);
}

/*
** Ajoute un pointeur dans la liste
** Renvoie 1 si erreur
*/
short	memory_add(t_memory *mem, void *ptr)
{
	t_node	*new_entry;

	if (!mem || !ptr)
		return (1);
	new_entry = malloc(sizeof(t_node));
	if (!new_entry)
		return (1);
	new_entry->content = ptr;
	new_entry->next = mem->head;
	mem->head = new_entry;
	return (0);
}

/*
** Supprime un pointeur spécifique
*/
short	memory_remove_one(t_memory *mem, void *ptr)
{
	t_node	*current;
	t_node	*previous;

	if (!mem || !ptr)
		return (1);
	current = mem->head;
	previous = NULL;
	while (current)
	{
		if (current->content == ptr)
		{
			if (previous)
				previous->next = current->next;
			else
				mem->head = current->next;
			free(current->content);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (1);
}

/*
** Libère tous les blocs enregistrés
*/
void	memory_cleanup(t_memory *mem)
{
	t_node	*current;
	t_node	*to_deallocate;

	if (!mem)
		return ;
	current = mem->head;
	while (current)
	{
		to_deallocate = current;
		current = current->next;
		free(to_deallocate->content);
		free(to_deallocate);
	}
	free(mem);
}

/*
** Affiche les blocs pour debug
*/
void	memory_debug_display(t_memory *mem)
{
	t_node	*current;
	int		i;

	if (!mem)
		return ;
	i = 0;
	current = mem->head;
	printf("Liste des allocs :\n");
	while (current)
	{
		printf("[%d] %p\n", i, current->content);
		current = current->next;
		i++;
	}
}
