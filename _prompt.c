#include "shell.h"

/**
 * _exit - exits the shell
 * @info: potential arguments
 *
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Unrecognized input: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes current directory of process
 * @info: potential arguments
 *
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *directory, buffer[1024];
	int newdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			newdir_ret = /* TODO: which input to insert? */
				newdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			newdir_ret = newdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		newdir_ret = /* TODO: which input to insert? */
			newdir((directory = _getenv(info, "OLDPWD=")) ? directoy : "/");
	}
	else
		newdir_ret = newdir(info->argv[1]);
	if (newdir_ret == -1)
	{
		print_error(info, "can't change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes current directory of process
 * @info potential arguments
 *
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help alert. Function not available \n");
	if (0)
		_puts(*arg_array); 
	return (0);
}
