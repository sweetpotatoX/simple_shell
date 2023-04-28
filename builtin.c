#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
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
 * _mycd - changes current working directory
 * @info: pointer to struct of shell info
 *
 * Return: 0 on success, 1 on error
 */
int _mycd(info_t *info)
{
	char *stringer, *direr, buff[1024];
	int chdirer_retu;

	/* get current working directory */
	stringer = getcwd(buff, 1024);
	if (!stringer)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	/* if no argument, change to home directory */
	if (!info->argv[1])
	{
		direr = _getenv(info, "HOME=");
		if (!direr)
			chdirer_retu = 
				chdir((direr = _getenv(info, "PWD=")) ? direr : "/");
		else
			chdirer_retu = chdir(direr);
	}
	/* if argument is "-", change to previous directory */
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			/* print current directory */
			_puts(stringer);
			_putchar('\n');
			return (1);
		}
		/* print previous directory and change to it */
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirer_retu = /* TODO: what should this be? */
			chdir((direr = _getenv(info, "OLDPWD=")) ? direr : "/");
	}
	/* change to specified directory */
	else
		chdirer_retu = chdir(info->argv[1]);

	/* if change directory failed, print error message */
	if (chdirer_retu == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	/* update environment variables for new working directory */
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - displays help information about shell builtins
 * @info: pointer to struct of command info
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array; /* declare variable with descriptive name */

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n"); /* print a message indicating help is not yet implemented */
	if (0)
		_puts(*arg_array); /* temporary workaround to avoid unused variable warning */
	return (0);
}


