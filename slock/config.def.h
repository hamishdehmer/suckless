/* user and group to drop privileges to */
static const char *user  = "ziox";
#define COLORC "red"
#define COLORC "red"
static const char *group = "wheel";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#203a41",   /* during input */
	[FAILED] = "#392f32",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
