#include "../minishell.h"
static int	ft_isspace2(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\n')
		return (1);
	return (0);
}
static bool	isemptystring2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace2(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*add_char(char *ret, char add)
{
	char	*added;
	size_t	i;

	added = ft_calloc(ft_strlen(ret) + 2, 1);
	i = 0;
	if (!added)
		return (NULL);
	if (!ret)
		added[0] = add;
	while (ret[i])
	{
		added[i] = ret[i];
		i++;
	}
	added[i] = add;
	ft_free(ret);
	ret = NULL;
	return (added);
}

char	*ft_strjoin_at(char *s1, char *s2, t_lexer *l)
{
	size_t	i;
	size_t	x;
	char	*join;

	i = 0;
	x = 0;
	// printf(ANSI_MAGENTA"JOINSTART\n");
	if (*s1 == 0)
	{
		ft_free(s1);
		s1 = l->str;
		// printf("l.str = %s\n", l->str);
	}
		// printf("s1 = %s\n", s1);
	if (!s1 || !s2)
		return (NULL);
	// printf("len s1 = %zu, len s2 = %zu === %zu\n", ft_strlen(s1), ft_strlen(s2), (ft_strlen(s1) + ft_strlen(s2)));
	// printf("at position %zu and c = %c\n", l->position, s1[l->position]);
	// printf("l.read = %zu\n", l->read);
	join = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i]) //this makes it stop from the input str NOT the ret str...
	// how do i keep track of curr $ position, how will i fill ret without losing input str
	{
		join[i] = s1[i];
		// printf("join[i = %zu] == %c\n", i, join[i]);
		i++;
	}
	while (s2[x])
	{
		// printf("join s2 '%c'\n", s2[x]);
		join[i] = s2[x];
		i++;
		x++;
	}
	// printf("stopped at '%c'\n", s2[x]);
	ft_free(s1);
	ft_free(s2);
	s1 = NULL;
	s2 = NULL;
	// l->position = l->read;
	// l->read = 0;
	// join[i] = 0;
		// printf("stopped iter '%zu'\n", i);
		// printf("join len '%zu'\n", ft_strlen(join));
		// printf("l.pos = %zu\n", l->position);
		// printf("l.read = %zu\n", l->read);
	// printf("JOIN END\n"ANSI_RESET);
	return (join);
}

static t_lexer	init_lexs(char *input)
{
	t_lexer	lex;

	lex.str = input;
	lex.position = 0;
	lex.read = 0;
	lex.last_c = 0;
	lex.curr_c = 0;
	return (lex);
}

char	*check_val(char *s, t_lexer *l)
{
	char	*sub;
	char	*val;

	l->read = l->position + 1;
	while (s[l->read] != '$' && s[l->read] != ' ' && s[l->read] != 0)
	{
		printf("read++\n");
		l->read++;
	}
		printf(ANSI_GREEN"l.pos = %zu\n", l->position);
		printf("l.read = %zu\n"ANSI_RESET, l->read);
	sub = ft_substr(s, l->position + 1, l->read - l->position - 1);
	printf("sub = %s\n", sub);
	val = getenv(sub);
	ft_free(sub);
	sub = NULL;
	if (val == NULL)
		return (NULL);
	printf("val = %s\n", val);
	return (val);
}

char	*get_exp_str(char *s, int type)
{
	t_lexer	l;
	char	*val;
	char	*ret;
	bool	sq;

	l = init_lexs(s);
	ret = ft_strdup("");
	if (type == SINGLE_Q)
		sq = true;
	while (s[l.position])
	{
		if (s[l.position] == '$' && !sq)
		{
			// printf(ANSI_RED"$$$$$$$$$WARUM?!?!?!?\n"ANSI_RESET);
			printf("at position %zu and c = \'%c\'\n", l.position, s[l.position]);
			printf("l.read = %zu\n", l.read);
			val = check_val(s, &l);
			if (val)
				ret = ft_strjoin_at(ret, val, &l);
			// else
			// {
			// 	printf(ANSI_BG_BRIGHT_BLUE"HELLOOO we are at pos %zu\n"ANSI_RESET, l.position);
				l.position = l.read;
			// 	printf("no val, at position %zu and c = \'%c\'\n", l.position, s[l.position]);
			// 	printf("l.read = %zu\n", l.read);
			// }
		}
		else
		{
			ret = add_char(ret, s[l.position]);
			printf(ANSI_BRIGHT_YELLOW"curr ret = \"%s\"\n"ANSI_RESET, ret);
			l.position++;
		}
		printf("strjoin RET = %s\n", ret);
			// else remove $ and subtring
		// printf(ANSI_RED"WARUM?!?!?!?\n"ANSI_RESET);
	}
	printf("\n\nEXP STR RET = %s\n", ret);
	return (ret);
}

char	*check_expand(char *s, int type)
{
	if (type == WORD || PATH)
		if (ft_strchr(s, '\'') || ft_strchr(s, '\"'))
			return (get_exp_str(s, type));
	if (type == SINGLE_Q || DOUBLE_Q)
	{
		// ft_strtrim()
		if (ft_strchr(s, '\'') || ft_strchr(s, '\"'))
			return (get_exp_str(s, type));
	}
	return (NULL);
}

char	*expand_tokens(t_token **toktop)
{
	t_token	*tmp;

	tmp = *toktop;
	while (tmp)
	{
		if (tmp->type == SINGLE_Q || DOUBLE_Q || WORD || PATH)
			tmp->str = check_expand(tmp->str, tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

// go through string until $
// then continue scanning until its ' ' or \0 or $,
// take that scan and put it in getenv
// insert getenv str into $position, not losing what is behind it
// continue looking for the end or more $ i.e. repeat loop

// if a path has something like hey'$USER'wassup, it ends up like this  hey'$USER'wassup...
// WORD can also have a string with quotes!!!!!!!!!!!! which is why the DOUBLE_Q and S_Q types are useless
// "hi"'$USER'"come here" = argc + 1 but $USER will be handled individually since its not in the "" part...

int main()
{
	init_garbage_collector();
	char	*test = ft_strdup("hi $USER$shit so what is it $USER ?");
	// t_lexer l = init_lexs(test);
	get_exp_str(test, WORD);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	// printf("test %s\n",  expand_quote(test, DOUBLE_Q));
}