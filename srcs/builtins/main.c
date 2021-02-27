#include <stdio.h>

int	bash_cd(char **av);
int	bash_pwd(char **av);
int	bash_env(char **av, char **envp);

int main(int argc, char **av, char **envp)
{
	(void)argc;
	bash_env(av, envp);
}