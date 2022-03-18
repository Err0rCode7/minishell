
#include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT) // Interruput
	{
		rl_on_new_line(); // readline 내부 시스템 초기화 선언
		rl_redisplay(); // newline이면 prompt + rl_line_buffer 출력
		ft_putendl_fd("  ", STDOUT);
		rl_on_new_line(); // prompt regenerate
		rl_replace_line("", 0); // rl_line_buffer 를 ""로 초기화 0은 undo_list 초기화 할지 말지 결정 0이면 안하는 것
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signo == SIGQUIT) // QUIT
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b\a", STDOUT); // back space * 2 + Alarm
	}
}

void	ignore_sig(int signo)
{
	// Quit 하고 \n 추가
	(void)signo;
	return ;
}

void	ignore_signal(void (*handle)(int))
{
	(void)handle;
	signal(SIGINT, ignore_sig);
	signal(SIGQUIT, ignore_sig);
}

void	init_signal(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
