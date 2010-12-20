
#define EXTUNIX_WANT_PTS
#include "config.h"

#if defined(EXTUNIX_HAVE_PTS)

static int open_flag_table[] = {
  O_RDONLY, O_WRONLY, O_RDWR, O_NONBLOCK, O_APPEND, O_CREAT, O_TRUNC, O_EXCL,
  O_NOCTTY, O_DSYNC, O_SYNC, O_RSYNC
};

CAMLprim value caml_posix_openpt(value flags)
{
	CAMLparam1(flags);
	int ret, cv_flags;
	cv_flags = caml_convert_flag_list(flags, open_flag_table);
	ret = posix_openpt(cv_flags);
	if(ret == -1)
		uerror("posix_openpt", Nothing);
	CAMLreturn(Val_int(ret));
}

CAMLprim value caml_grantpt(value fd)
{
	CAMLparam1(fd);
	if(grantpt(Int_val(fd)) == -1)
		uerror("grantpt", Nothing);
	CAMLreturn(Val_unit); 
}

CAMLprim value caml_unlockpt(value fd)
{
	CAMLparam1(fd);
	if(unlockpt(Int_val(fd)) == -1)
		uerror("unlockpt", Nothing);
	CAMLreturn(Val_unit); 
}

CAMLprim value caml_ptsname(value fd)
{
	CAMLparam1(fd);
	CAMLlocal1(ret);
	char *name = ptsname(Int_val(fd));
	if(name == 0)
		uerror("ptsname", Nothing);
	ret = caml_copy_string(name);
	CAMLreturn(ret);
}


#endif /* HAVE_PTS */