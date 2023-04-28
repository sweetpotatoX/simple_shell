#include "shell.h"

/**
 * _myexit - Exits the shel
 * @info: Structure containing potential arguments
 *
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
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
 *
 *_mycd - Changes current working directory
 *@info: Pointer to struct of shell info
 *Return: 0 on success, 1 on error
*/
int _mycd(info_t *info)
{
char *stringer, *direr, buff[1024];
int chdirer_retu;
stringer = getcwd(buff, 1024);
if (!stringer)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
direr = _getenv(info, "HOME=");
if (!direr)
chdirer_retu = chdir((direr = _getenv(info, "PWD=")) ? direr : "/");
else
chdirer_retu = chdir(direr);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(stringer);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD="));
_putchar('\n');
chdirer_retu = chdir((direr = _getenv(info, "OLDPWD=")) ? direr : "/");
}
else
chdirer_retu = chdir(info->argv[1]);
if (chdirer_retu == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]);
_eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buff, 1024));
}
return (0);
}

/**
 * _myhelp - Displays help information about shell builtins
 * @info: Pointer to struct of command info
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* Temporary workaround to avoid unused variable warning*/
	return (0);
}
