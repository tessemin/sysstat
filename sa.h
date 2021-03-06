/*
 * sar/sadc: Report system activity
 * (C) 1999-2017 by Sebastien Godard (sysstat <at> orange.fr)
 */

#ifndef _SA_H
#define _SA_H

#include <stdio.h>

#include "common.h"
#include "rd_stats.h"
#include "rd_sensors.h"

/*
 ***************************************************************************
 * Activity identification values.
 ***************************************************************************
 */

/* Number of activities */
#define NR_ACT		39
/* The value below is used for sanity check */
#define MAX_NR_ACT	256

/* Number of functions used to count items */
#define NR_F_COUNT	11

/* Activities */
#define A_CPU		1
#define A_PCSW		2
#define A_IRQ		3
#define A_SWAP		4
#define A_PAGE		5
#define A_IO		6
#define A_MEMORY	7
#define A_KTABLES	8
#define A_QUEUE		9
#define A_SERIAL	10
#define A_DISK		11
#define A_NET_DEV	12
#define A_NET_EDEV	13
#define A_NET_NFS	14
#define A_NET_NFSD	15
#define A_NET_SOCK	16
#define A_NET_IP	17
#define A_NET_EIP	18
#define A_NET_ICMP	19
#define A_NET_EICMP	20
#define A_NET_TCP	21
#define A_NET_ETCP	22
#define A_NET_UDP	23
#define A_NET_SOCK6	24
#define A_NET_IP6	25
#define A_NET_EIP6	26
#define A_NET_ICMP6	27
#define A_NET_EICMP6	28
#define A_NET_UDP6	29
#define A_PWR_CPUFREQ	30
#define A_PWR_FAN	31
#define A_PWR_TEMP	32
#define A_PWR_IN	33
#define A_HUGE		34
#define A_PWR_WGHFREQ	35
#define A_PWR_USB	36
#define A_FILESYSTEM	37
#define A_NET_FC	38
#define A_NET_SOFT	39


/* Macro used to flag an activity that should be collected */
#define COLLECT_ACTIVITY(m)	act[get_activity_position(act, m, EXIT_IF_NOT_FOUND)]->options |= AO_COLLECTED

/* Macro used to flag an activity that should be selected */
#define SELECT_ACTIVITY(m)	act[get_activity_position(act, m, EXIT_IF_NOT_FOUND)]->options |= AO_SELECTED


/*
 ***************************************************************************
 * Flags.
 ***************************************************************************
 */

#define S_F_SINCE_BOOT		0x00000001
#define S_F_SA_ROTAT      	0x00000002
#define S_F_DEV_PRETTY		0x00000004
#define S_F_FORCE_FILE		0x00000008
#define S_F_INTERVAL_SET	0x00000010
#define S_F_TRUE_TIME		0x00000020
#define S_F_LOCK_FILE		0x00000040
#define S_F_SEC_EPOCH		0x00000080
#define S_F_HDR_ONLY		0x00000100
#define S_F_FILE_LOCKED		0x00000200
#define S_F_SA_YYYYMMDD		0x00000400
#define S_F_HORIZONTALLY	0x00000800
#define S_F_COMMENT		0x00001000
#define S_F_PERSIST_NAME	0x00002000
#define S_F_LOCAL_TIME		0x00004000
#define S_F_PREFD_TIME_OUTPUT	0x00008000
#define S_F_SVG_SKIP		0x00010000
/* Same value as S_F_SVG_SKIP above. Used for a different output format */
#define S_F_RAW_SHOW_HINTS	0x00010000
#define S_F_SVG_AUTOSCALE	0x00020000
#define S_F_SVG_ONE_DAY		0x00040000
#define S_F_SVG_SHOW_IDLE	0x00080000
#define S_F_UNIT		0x00100000
#define S_F_SVG_HEIGHT		0x00200000
#define S_F_SVG_PACKED		0x00400000
#define S_F_SVG_SHOW_INFO	0x00800000

#define WANT_SINCE_BOOT(m)		(((m) & S_F_SINCE_BOOT)   == S_F_SINCE_BOOT)
#define WANT_SA_ROTAT(m)		(((m) & S_F_SA_ROTAT)     == S_F_SA_ROTAT)
#define USE_PRETTY_OPTION(m)		(((m) & S_F_DEV_PRETTY)   == S_F_DEV_PRETTY)
#define FORCE_FILE(m)			(((m) & S_F_FORCE_FILE)   == S_F_FORCE_FILE)
#define INTERVAL_SET(m)			(((m) & S_F_INTERVAL_SET) == S_F_INTERVAL_SET)
#define PRINT_TRUE_TIME(m)		(((m) & S_F_TRUE_TIME)    == S_F_TRUE_TIME)
#define LOCK_FILE(m)			(((m) & S_F_LOCK_FILE)    == S_F_LOCK_FILE)
#define PRINT_SEC_EPOCH(m)		(((m) & S_F_SEC_EPOCH)    == S_F_SEC_EPOCH)
#define DISPLAY_HDR_ONLY(m)		(((m) & S_F_HDR_ONLY)     == S_F_HDR_ONLY)
#define FILE_LOCKED(m)			(((m) & S_F_FILE_LOCKED)  == S_F_FILE_LOCKED)
#define USE_SA_YYYYMMDD(m)		(((m) & S_F_SA_YYYYMMDD)  == S_F_SA_YYYYMMDD)
#define DISPLAY_HORIZONTALLY(m)		(((m) & S_F_HORIZONTALLY) == S_F_HORIZONTALLY)
#define DISPLAY_COMMENT(m)		(((m) & S_F_COMMENT)      == S_F_COMMENT)
#define DISPLAY_PERSIST_NAME_S(m)	(((m) & S_F_PERSIST_NAME) == S_F_PERSIST_NAME)
#define PRINT_LOCAL_TIME(m)		(((m) & S_F_LOCAL_TIME)   == S_F_LOCAL_TIME)
#define USE_PREFD_TIME_OUTPUT(m)	(((m) & S_F_PREFD_TIME_OUTPUT)   == S_F_PREFD_TIME_OUTPUT)
#define SKIP_EMPTY_VIEWS(m)		(((m) & S_F_SVG_SKIP)     == S_F_SVG_SKIP)
#define DISPLAY_HINTS(m)		(((m) & S_F_RAW_SHOW_HINTS) == S_F_RAW_SHOW_HINTS)
#define AUTOSCALE_ON(m)			(((m) & S_F_SVG_AUTOSCALE) == S_F_SVG_AUTOSCALE)
#define DISPLAY_ONE_DAY(m)		(((m) & S_F_SVG_ONE_DAY)   == S_F_SVG_ONE_DAY)
#define DISPLAY_IDLE(m)			(((m) & S_F_SVG_SHOW_IDLE) == S_F_SVG_SHOW_IDLE)
#define DISPLAY_INFO(m)			(((m) & S_F_SVG_SHOW_INFO) == S_F_SVG_SHOW_INFO)
#define DISPLAY_UNIT(m)			(((m) & S_F_UNIT) == S_F_UNIT)
#define SET_CANVAS_HEIGHT(m)		(((m) & S_F_SVG_HEIGHT) == S_F_SVG_HEIGHT)
#define PACK_VIEWS(m)			(((m) & S_F_SVG_PACKED) == S_F_SVG_PACKED)

#define AO_F_NULL		0x00000000

/* Output flags for options -r / -S */
#define AO_F_MEMORY		0x00000001
#define AO_F_SWAP		0x00000002
/* AO_F_MEM_ALL: See opt_flags in struct activity below */
#define AO_F_MEM_ALL		(AO_F_MEMORY << 8)

#define DISPLAY_MEMORY(m)	(((m) & AO_F_MEMORY)	== AO_F_MEMORY)
#define DISPLAY_SWAP(m)		(((m) & AO_F_SWAP)	== AO_F_SWAP)
#define DISPLAY_MEM_ALL(m)	(((m) & AO_F_MEM_ALL)	== AO_F_MEM_ALL)

/* Output flags for option -u [ ALL ] */
#define AO_F_CPU_DEF		0x00000001
#define AO_F_CPU_ALL		0x00000002

#define DISPLAY_CPU_DEF(m)	(((m) & AO_F_CPU_DEF)     == AO_F_CPU_DEF)
#define DISPLAY_CPU_ALL(m)	(((m) & AO_F_CPU_ALL)     == AO_F_CPU_ALL)

/* Output flags for option -d */
#define AO_F_DISK_PART		0x00000001

#define COLLECT_PARTITIONS(m)	(((m) & AO_F_DISK_PART)   == AO_F_DISK_PART)

/* Output flags for option -F */
#define AO_F_FILESYSTEM		0x00000001
#define AO_F_MOUNT		0x00000002

#define DISPLAY_MOUNT(m)	(((m) & AO_F_MOUNT)       == AO_F_MOUNT)

/*
 ***************************************************************************
 * Various keywords and constants.
 ***************************************************************************
 */

/* Keywords */
#define K_XALL		"XALL"
#define K_SUM		"SUM"
#define K_DEV		"DEV"
#define K_EDEV		"EDEV"
#define K_NFS		"NFS"
#define K_NFSD		"NFSD"
#define K_SOCK		"SOCK"
#define K_IP		"IP"
#define K_EIP		"EIP"
#define K_ICMP		"ICMP"
#define K_EICMP		"EICMP"
#define K_TCP		"TCP"
#define K_ETCP		"ETCP"
#define K_UDP		"UDP"
#define K_SOCK6		"SOCK6"
#define K_IP6		"IP6"
#define K_EIP6		"EIP6"
#define K_ICMP6		"ICMP6"
#define K_EICMP6	"EICMP6"
#define K_UDP6		"UDP6"
#define K_CPU		"CPU"
#define K_FAN		"FAN"
#define K_TEMP		"TEMP"
#define K_IN		"IN"
#define K_FREQ		"FREQ"
#define K_MOUNT		"MOUNT"
#define K_FC		"FC"
#define K_SOFT		"SOFT"

#define K_INT		"INT"
#define K_DISK		"DISK"
#define K_XDISK		"XDISK"
#define K_SNMP		"SNMP"
#define K_IPV6		"IPV6"
#define K_POWER		"POWER"
#define K_USB		"USB"

#define K_SKIP_EMPTY	"skipempty"
#define K_AUTOSCALE	"autoscale"
#define K_ONEDAY	"oneday"
#define K_SHOWIDLE	"showidle"
#define K_SHOWINFO	"showinfo"
#define K_SHOWHINTS	"showhints"
#define K_HEIGHT	"height="
#define K_PACKED	"packed"

/* Groups of activities */
#define G_DEFAULT	0x00
#define G_INT		0x01
#define G_DISK		0x02
#define G_SNMP		0x04
#define G_IPV6		0x08
#define G_POWER		0x10
#define G_XDISK		0x20

/* sadc program */
#define SADC		"sadc"

/* Time must have the format HH:MM:SS with HH in 24-hour format */
#define DEF_TMSTART	"08:00:00"
#define DEF_TMEND	"18:00:00"

#define UTSNAME_LEN	65
#define HEADER_LINE_LEN	512

/*
 * Define upper limit for various items.
 * Made necessary because we have to check the number of
 * items for each activity when we read a (possibly tainted)
 * sa data file.
 */
#define MAX_NR_SERIAL_LINES	65536
#define MAX_NR_DISKS		(65536 * 4096)
#define MAX_NR_IFACES		65536
#define MAX_NR_FANS		4096
#define MAX_NR_TEMP_SENSORS	4096
#define MAX_NR_IN_SENSORS	4096
#define MAX_NR_USB		65536
#define MAX_NR_FS		(65536 * 4096)
#define MAX_NR_FCHOSTS		65536

/* NR_MAX is the upper limit used for unknown activities */
#define NR_MAX		(65536 * 4096)
#define NR2_MAX		1024

/* Maximum number of args that can be passed to sadc */
#define MAX_ARGV_NR	32

/* Miscellaneous constants */
#define USE_SADC		0
#define USE_SA_FILE		1
#define NO_TM_START		0
#define NO_TM_END		0
#define NO_RESET		0
#define NON_FATAL		0
#define FATAL			1
#define C_SAR			0
#define C_SADF			1
#define ALL_ACTIVITIES		~0U
#define EXIT_IF_NOT_FOUND	1
#define RESUME_IF_NOT_FOUND	0

#define SOFT_SIZE	0
#define HARD_SIZE	1

#define FIRST	0
#define SECOND	1

#define CLOSE_XML_MARKUP	0
#define OPEN_XML_MARKUP		1

#define CLOSE_JSON_MARKUP	0
#define OPEN_JSON_MARKUP	1

#define COUNT_ACTIVITIES	0
#define COUNT_OUTPUTS		1

/* Type for all functions counting items */
#define __nr_t		int
/* Type for all functions reading statistics */
#define __read_funct_t	void
/* Type for all functions displaying statistics */
#define __print_funct_t void

/* Structure for SVG specific parameters */
struct svg_parm {
	unsigned long long dt;			/* Interval of time for current sample */
	unsigned long long ust_time_ref;	/* X axis start time in seconds since the epoch */
	unsigned long long ust_time_end;	/* X axis end time in seconds since the epoch */
	unsigned long long ust_time_first;	/* Time (in seconds since the epoch) for first sample */
	int graph_no;				/* Total number of views already displayed */
	int restart;				/* TRUE if we have just met a RESTART record */
	struct file_header *file_hdr;		/* Pointer on file header structure */
};

/* Structure used when displaying SVG header */
struct svg_hdr_parm {
	int graph_nr;	   /* Number of rows of views to display or canvas height entered on the command line */
	int views_per_row; /* Maximum number of views on a single row */
};

/*
 ***************************************************************************
 * Definitions of header structures.
 *
 * The rule is: "strict writing, broad reading", meaning that sar/sadc can
 * only append data to a datafile whose format is strictly the same as that
 * of current version (checking FORMAT_MAGIC is not enough), but sar/sadf
 * can read data from different versions, providing that FORMAT_MAGIC value
 * has not changed.
 *
 * Format of system activity data files:
 *	 __
 *	|
 *	| file_magic structure
 *	|
 * 	|--
 *	|
 * 	| file_header structure
 * 	|
 * 	|--                         --|
 * 	|                             |
 * 	| file_activity structure     | * sa_act_nr
 * 	|                             |
 * 	|--                         --|
 * 	|                             |
 * 	| record_header structure     |
 * 	|                             |
 * 	|--                           | * <count>
 * 	|                             |
 * 	| Statistics structures...(*) |
 * 	|                             |
 * 	|--                         --|
 *
 * (*)Note: If it's a special record, we may find a comment instead of
 * statistics (R_COMMENT record type) or, if it's a R_RESTART record type,
 * <sa_nr_vol_act> structures (of type file_activity) for the volatile
 * activities.
 ***************************************************************************
 */

/*
 * Sysstat magic number. Should never be modified.
 * Indicate that the file was created by sysstat.
 */
#define SYSSTAT_MAGIC	0xd596
#define SYSSTAT_MAGIC_SWAPPED	(((SYSSTAT_MAGIC << 8) | (SYSSTAT_MAGIC >> 8)) & 0xffff)

/*
 * Datafile format magic number.
 * Modified to indicate that the format of the file is
 * no longer compatible with that of previous sysstat versions.
 */
#define FORMAT_MAGIC	0x2175
#define FORMAT_MAGIC_SWAPPED	(((FORMAT_MAGIC << 8) | (FORMAT_MAGIC >> 8)) & 0xffff)

/* Previous datafile format magic number used by older sysstat versions */
#define PREVIOUS_FORMAT_MAGIC	0x2173

/* Padding in file_magic structure. See below. */
#define FILE_MAGIC_PADDING	48

/* Structure for file magic header data */
struct file_magic {
	/*
	 * This field identifies the file as a file created by sysstat.
	 */
	unsigned short sysstat_magic;
	/*
	 * The value of this field varies whenever datafile format changes.
	 */
	unsigned short format_magic;
	/*
	 * Sysstat version used to create the file.
	 */
	unsigned char sysstat_version;
	unsigned char sysstat_patchlevel;
	unsigned char sysstat_sublevel;
	unsigned char sysstat_extraversion;
#define FILE_MAGIC_ULL_NR	0	/* Nr of unsigned long long below */
#define FILE_MAGIC_UL_NR	0	/* Nr of unsigned long below */
#define FILE_MAGIC_U_NR		5	/* Nr of [unsigned] int below */
	/*
	 * Size of file's header (size of file_header structure used by file).
	 */
	unsigned int header_size;
	/*
	 * Set to non zero if data file has been converted with "sadf -c" from
	 * an old format (version x.y.z) to a newest format (version X.Y.Z).
	 * In this case, the value is: Y*256 + Z + 1.
	 * The FORMAT_MAGIC value of the file can be used to determine X.
	 */
	unsigned int upgraded;
	/*
	 * Description of the file_header structure
	 * (nr of "long long", nr of "long" and nr of "int").
	 */
	unsigned int hdr_types_nr[3];
	/*
	 * Padding. Reserved for future use while avoiding a format change.
	 * sysstat always reads a number of bytes which is that expected for
	 * current sysstat version (FILE_MAGIC_SIZE). We cannot guess if we
	 * are going to read a file from current, an older or a newer version.
	 */
	unsigned char pad[FILE_MAGIC_PADDING];
};

#define FILE_MAGIC_SIZE	(sizeof(struct file_magic))

/* Header structure for system activity data file */
struct file_header {
	/*
	 * Timestamp in seconds since the epoch.
	 */
	unsigned long long sa_ust_time;
	/*
	 * Number of jiffies per second.
	 */
	unsigned long sa_hz		__attribute__ ((aligned (8)));
	/*
	 * Number of CPU items (1 .. CPU_NR + 1) for the last sample in file.
	 */
	unsigned int sa_last_cpu_nr	__attribute__ ((aligned (8)));
	/*
	 * Number of [online or offline] CPU (1 .. CPU_NR + 1)
	 * when the datafile has been created.
	 * When reading a datafile, this value is updated whenever
	 * a RESTART record is found.
	 */
	unsigned int sa_cpu_nr;
	/*
	 * Number of activities saved in file.
	 */
	unsigned int sa_act_nr;
	/*
	 * Number of volatile activities in file. This is the number of
	 * file_activity structures saved after each restart mark in file.
	 */
	unsigned int sa_vol_act_nr;
	/*
	 * Current year.
	 */
	int sa_year;
	/*
	 * Description of the file_activity and record_header structures
	 * (nr of "long long", nr of "long" and nr of "int").
	 */
	unsigned int act_types_nr[3];
	unsigned int rec_types_nr[3];
	/*
	 * Size of file_activity and record_header structures used by file.
	 */
	unsigned int act_size;
	unsigned int rec_size;
	/*
	 * Current day and month.
	 * No need to save DST (Daylight Saving Time) flag, since it is not taken
	 * into account by the strftime() function used to print the timestamp.
	 */
	unsigned char sa_day;
	unsigned char sa_month;
	/*
	 * Size of a long integer. Useful to know the architecture on which
	 * the datafile was created.
	 */
	char sa_sizeof_long;
	/*
	 * Operating system name.
	 */
	char sa_sysname[UTSNAME_LEN];
	/*
	 * Machine hostname.
	 */
	char sa_nodename[UTSNAME_LEN];
	/*
	 * Operating system release number.
	 */
	char sa_release[UTSNAME_LEN];
	/*
	 * Machine architecture.
	 */
	char sa_machine[UTSNAME_LEN];
};

#define FILE_HEADER_SIZE	(sizeof(struct file_header))
#define FILE_HEADER_ULL_NR	1	/* Nr of unsigned long long in file_header structure */
#define FILE_HEADER_UL_NR	1	/* Nr of unsigned long in file_header structure */
#define FILE_HEADER_U_NR	13	/* Nr of [unsigned] int in file_header structure */
/* The values below are used for sanity check */
#define MIN_FILE_HEADER_SIZE	0
#define MAX_FILE_HEADER_SIZE	8192


/*
 * Base magical number for activities.
 */
#define ACTIVITY_MAGIC_BASE	0x8a
/*
 * Magical value used for activities with
 * unknown format (used for sadf -H only).
 */
#define ACTIVITY_MAGIC_UNKNOWN	0x89

/* List of activities saved in file */
struct file_activity {
	/*
	 * Identification value of activity.
	 */
	unsigned int id;
	/*
	 * Activity magical number.
	 */
	unsigned int magic;
	/*
	 * Number of items for this activity.
	 */
	__nr_t nr;
	/*
	 * Number of sub-items for this activity.
	 */
	__nr_t nr2;
	/*
	 * Size of an item structure.
	 */
	int size;
	/*
	 * Description of the structure containing statistics for the
	 * given activity (nr of "long long", nr of "long" and nr of "int").
	 */
	unsigned int types_nr[3];
};

#define FILE_ACTIVITY_SIZE	(sizeof(struct file_activity))
#define MAX_FILE_ACTIVITY_SIZE	1024	/* Used for sanity check */
#define FILE_ACTIVITY_ULL_NR	0	/* Nr of unsigned long long in file_activity structure */
#define FILE_ACTIVITY_UL_NR	0	/* Nr of unsigned long in file_activity structure */
#define FILE_ACTIVITY_U_NR	8	/* Nr of [unsigned] int in file_activity structure */


/* Record type */
/*
 * R_STATS means that this is a record of statistics.
 */
#define R_STATS		1
/*
 * R_RESTART means that this is a special record containing
 * a LINUX RESTART message.
 */
#define R_RESTART	2
/*
 * R_LAST_STATS warns sar that this is the last record to be written
 * to file before a file rotation, and that the next data to come will
 * be a header file.
 * Such a record is tagged R_STATS anyway before being written to file.
 */
#define R_LAST_STATS	3
/*
 * R_COMMENT means that this is a special record containing
 * a comment.
 */
#define R_COMMENT	4

/* Maximum length of a comment */
#define MAX_COMMENT_LEN	64

/* Header structure for every record */
struct record_header {
	/*
	 * Machine uptime in 1/100th of a second.
	 */
	unsigned long long uptime_cs;
	/*
	 * Timestamp (number of seconds since the epoch).
	 */
	unsigned long long ust_time;
	/*
	 * Record type: R_STATS, R_RESTART,...
	 */
	unsigned char record_type;
	/*
	 * Timestamp: Hour (0-23), minute (0-59) and second (0-59).
	 * Used to determine TRUE time (immutable, non locale dependent time).
	 */
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
};

#define RECORD_HEADER_SIZE	(sizeof(struct record_header))
#define MAX_RECORD_HEADER_SIZE	512	/* Used for sanity check */
#define RECORD_HEADER_ULL_NR	2	/* Nr of unsigned long long in record_header structure */
#define RECORD_HEADER_UL_NR	0	/* Nr of unsigned long in record_header structure */
#define RECORD_HEADER_U_NR	0	/* Nr of unsigned int in record_header structure */


/*
 ***************************************************************************
 * Generic description of an activity.
 ***************************************************************************
 */

/* Activity options */
#define AO_NULL			0x00
/*
 * Indicate that corresponding activity should be collected by sadc.
 */
#define AO_COLLECTED		0x01
/*
 * Indicate that corresponding activity should be displayed by sar.
 */
#define AO_SELECTED		0x02
/*
 * When appending data to a file, the number of items (for every activity)
 * is forced to that of the file (number of network interfaces, serial lines,
 * etc.) Exceptions are volatile activities (like A_CPU) whose number of items
 * is related to the number of CPUs: If current machine has a different number
 * of CPU than that of the file (but is equal to sa_last_cpu_nr) then data
 * will be appended with a number of items equal to that of the machine.
 */
#define AO_VOLATILE		0x04
/*
 * 0x08: Unused.
 */
/*
 * This flag should be set for every activity closing a markup used
 * by several activities. Used by sadf f_xml_print() functions to
 * display XML output.
 */
#define AO_CLOSE_MARKUP		0x10
/*
 * Indicate that corresponding activity has multiple different
 * output formats. This is the case for example for memory activity
 * with options -r and -R.
 * PS: Such an activity should appear in the list of activities that
 * sar -A is supposed to display.
 */
#define AO_MULTIPLE_OUTPUTS	0x20
/*
 * Indicate that one (SVG) graph will be displayed for each
 * distinct item for this activity (sadf -g).
 */
#define AO_GRAPH_PER_ITEM	0x40
/*
 * Indicate that this activity may have sub-items.
 */
#define AO_MATRIX		0x80

#define IS_COLLECTED(m)		(((m) & AO_COLLECTED)        == AO_COLLECTED)
#define IS_SELECTED(m)		(((m) & AO_SELECTED)         == AO_SELECTED)
#define IS_VOLATILE(m)		(((m) & AO_VOLATILE)         == AO_VOLATILE)
#define CLOSE_MARKUP(m)		(((m) & AO_CLOSE_MARKUP)     == AO_CLOSE_MARKUP)
#define HAS_MULTIPLE_OUTPUTS(m)	(((m) & AO_MULTIPLE_OUTPUTS) == AO_MULTIPLE_OUTPUTS)
#define ONE_GRAPH_PER_ITEM(m)	(((m) & AO_GRAPH_PER_ITEM)   == AO_GRAPH_PER_ITEM)
#define IS_MATRIX(m)		(((m) & AO_MATRIX)           == AO_MATRIX)

#define _buf0	buf[0]

/* Structure used to define a bitmap needed by an activity */
struct act_bitmap {
	/*
	 * Bitmap for activities that need one. Remember to allocate it
	 * before use!
	 */
	unsigned char *b_array;
	/*
	 * Size of the bitmap in bits. In fact, bitmap is sized to b_size + 1
	 * to take into account CPU "all"
	 */
	int b_size;
};

/*
 * Structure used to define an activity.
 * Note: This structure can be modified without changing the format of data files.
 */
struct activity {
	/*
	 * This variable contains the identification value (A_...) for this activity.
	 */
	unsigned int id;
	/*
	 * Activity options (AO_...)
	 */
	unsigned int options;
	/*
	 * Activity magical number. This number changes when activity format in file
	 * is no longer compatible with the format of that same activity from
	 * previous versions.
	 */
	unsigned int magic;
	/*
	 * An activity belongs to a group (and only one).
	 * Groups are those selected with option -S of sadc.
	 */
	unsigned int group;
	/*
	 * Index in f_count[] array to determine function used to count
	 * the number of items (serial lines, network interfaces, etc.) -> @nr
	 * Such a function should _always_ return a value greater than
	 * or equal to 0.
	 *
	 * A value of -1 indicates that the number of items
	 * is a constant (and @nr is set to this value).
	 *
	 * These functions are called even if corresponding activities have not
	 * been selected, to make sure that all items have been calculated
	 * (including #CPU, etc.)
	 */
	int f_count_index;
	/*
	 * The f_count2() function is used to count the number of
	 * sub-items -> @nr2
	 * Such a function should _always_ return a value greater than
	 * or equal to 0.
	 *
	 * A NULL value for this function pointer indicates that the number of items
	 * is a constant (and @nr2 is set to this value).
	 */
	__nr_t (*f_count2) (struct activity *);
	/*
	 * This function reads the relevant file and fill the buffer
	 * with statistics corresponding to given activity.
	 */
	__read_funct_t (*f_read) (struct activity *);
	/*
	 * This function displays activity statistics onto the screen.
	 */
	__print_funct_t (*f_print) (struct activity *, int, int, unsigned long long);
	/*
	 * This function displays average activity statistics onto the screen.
	 */
	__print_funct_t (*f_print_avg) (struct activity *, int, int, unsigned long long);
	/*
	 * This function is used by sadf to display activity in a format that can
	 * easily be ingested by a relational database, or a format that can be
	 * handled by pattern processing commands like "awk".
	 */
	__print_funct_t (*f_render) (struct activity *, int, char *, int, unsigned long long);
	/*
	 * This function is used by sadf to display activity statistics in XML.
	 */
	__print_funct_t (*f_xml_print) (struct activity *, int, int, unsigned long long);
	/*
	 * This function is used by sadf to display activity statistics in JSON.
	 */
	__print_funct_t (*f_json_print) (struct activity *, int, int, unsigned long long);
	/*
	 * This function is used by sadf to display activity statistics in SVG.
	 */
	__print_funct_t (*f_svg_print) (struct activity *, int, int, struct svg_parm *,
					unsigned long long, struct record_header *);
	/*
	 * This function is used by sadf to display activity statistics in raw format.
	 */
	__print_funct_t (*f_raw_print) (struct activity *, char *, int);
	/*
	 * Header string displayed by sadf -d.
	 * Header lines for each output (for activities with multiple outputs) are
	 * separated with a '|' character.
	 * For a given output, the first field corresponding to extended statistics
	 * (eg. -r ALL) begins with a '&' character.
	 */
	char *hdr_line;
	/*
	 * Name of activity.
	 */
	char *name;
	/*
	 * Description of the corresponding structure containing statistics (as defined
	 * in rd_stats.h or rd_sensors.h). Such a structure has 0+ fields of type
	 * "long long", followed by 0+ fields of type "long", followed by 0+ fields of
	 * type "int", followed by 0+ other fields (e.g. of type char). The array below
	 * gives the number of "long long" fields composing the structure, then the number
	 * of "long" fields, then the number of "int" fields.
	 */
	unsigned int gtypes_nr[3];
	/*
	 * This array has the same meaning as @gtypes_nr[] above, but the values are those
	 * read from current data file. They may be different from those of @gtypes_nr[]
	 * because we can read data from a different sysstat version (older or newer).
	 */
	unsigned int ftypes_nr[3];
	/*
	 * Number of SVG graphs for this activity. The total number of graphs for
	 * the activity can be greater though if flag AO_GRAPH_PER_ITEM is set, in
	 * which case the total number will  be @g_nr * @nr.
	 */
	int g_nr;
	/*
	 * Number of items on the system.
	 * A negative value (-1) is the default value and indicates that this number
	 * has still not been calculated by the f_count() function.
	 * A value of 0 means that this number has been calculated, but no items have
	 * been found.
	 * A positive value (>0) has either been calculated or is a constant.
	 */
	__nr_t nr;
	/*
	 * Number of sub-items on the system.
	 * @nr2 is in fact the second dimension of a matrix of items, the first
	 * one being @nr. @nr is the number of lines, and @nr2 the number of columns.
	 * A negative value (-1) is the default value and indicates that this number
	 * has still not been calculated by the f_count2() function.
	 * A value of 0 means that this number has been calculated, but no sub-items have
	 * been found.
	 * A positive value (>0) has either been calculated or is a constant.
	 * Rules:
	 * 1) IF @nr2 = 0 THEN @nr = 0
	 *    Note: If @nr = 0, then @nr2 is undetermined (may be -1, 0 or >0).
	 * 2) IF @nr > 0 THEN @nr2 > 0.
	 *    Note: If @nr2 > 0 then @nr is undetermined (may be -1, 0 or >0).
	 * 3) IF @nr <= 0 THEN @nr2 = -1 (this is the default value for @nr2,
	 * meaning that it has not been calculated).
	 */
	__nr_t nr2;
	/*
	 * Maximum number of elements that sar can handle for this item.
	 * NB: The maximum number of elements that sar can handle for sub-items
	 * is NR2_MAX.
	 */
	__nr_t nr_max;
	/*
	 * Size of an item.
	 * This is the size of the corresponding structure, as read from or written
	 * to a file, or read from or written by the data collector.
	 */
	int fsize;
	/*
	 * Size of an item.
	 * This is the size of the corresponding structure as mapped into memory.
	 * @msize can be different from @fsize when data are read from or written to
	 * a data file from a different sysstat version.
	 */
	int msize;
	/*
	 * Optional flags for activity. This is eg. used when AO_MULTIPLE_OUTPUTS
	 * option is set.
	 * 0x0001 - 0x0080 : Multiple outputs (eg. AO_F_MEMORY, AO_F_SWAP...)
	 * 0x0100 - 0x8000 : If bit set then display complete header (hdr_line) for
	 *                   corresponding output
	 * 0x010000+       : Optional flags
	 */
	unsigned int opt_flags;
	/*
	 * Buffers that will contain the statistics read. Its size is @nr * @nr2 * @size each.
	 * [0]: used by sadc.
	 * [0] and [1]: current/previous statistics values (used by sar).
	 * [2]: Used by sar to save first collected stats (used later to
	 * compute average).
	 */
	void *buf[3];
	/*
	 * Bitmap for activities that need one. Such a bitmap is needed by activity
	 * if @bitmap is not NULL.
	 */
	struct act_bitmap *bitmap;
};


/*
 ***************************************************************************
 * Generic description of an output format for sadf (and sar).
 ***************************************************************************
 */

/* Type for all functions used by sadf to display stats in various formats */
#define __printf_funct_t void
#define __tm_funct_t char *

/*
 * Structure used to define a report.
 * A XML-like report has the following format:
 *       __
 *      |
 *      | Header block
 *      |  __
 *      | |
 *      | | Statistics block
 *      | |  __
 *      | | |
 *      | | | Timestamp block
 *      | | |  __
 *      | | | |
 *      | | | | Activity #1
 *      | | | |__
 *      | | | |
 *      | | | | ...
 *      | | | |__
 *      | | | |
 *      | | | | Activity #n
 *      | | | |__
 *      | | |__
 *      | |__
 *      | |
 *      | | Restart messages block
 *      | |__
 *      | |
 *      | | Comments block
 *      | |__
 *      |__
 */
struct report_format {
	/*
	 * This variable contains the identification value (F_...) for this report format.
	 */
	unsigned int id;
	/*
	 * Format options (FO_...).
	 */
	unsigned int options;
	/*
	 * This function displays the report header
	 * (data displayed once at the beginning of the report).
	 */
	__printf_funct_t (*f_header) (void *, int, char *, struct file_magic *, struct file_header *,
				      struct activity * [], unsigned int []);
	/*
	 * This function defines the statistics part of the report.
	 * Used only with textual (XML-like) reports.
	 */
	__printf_funct_t (*f_statistics) (int *, int);
	/*
	 * This function defines the timestamp part of the report.
	 * Used only with textual (XML-like) reports.
	 */
	__tm_funct_t (*f_timestamp) (void *, int, char *, char *, unsigned long long,
				     struct file_header *, unsigned int);
	/*
	 * This function displays the restart messages.
	 */
	__printf_funct_t (*f_restart) (int *, int, char *, char *, int, struct file_header *);
	/*
	 * This function displays the comments.
	 */
	__printf_funct_t (*f_comment) (int *, int, char *, char *, int, char *, struct file_header *);
};

/* Possible actions for functions used to display reports */
#define F_BEGIN	0x01
#define F_MAIN	0x02
#define F_END	0x04

/*
 ***************************************************************************
 * SVG output definitions
 ***************************************************************************
 */

/*
 *   ^
 * 1 | General header
 *   v
 *   ^   ^   ^
 *   |   | 4 | Graph title
 *   |   |   v
 *   |   |   ^    |                                Caption
 *   | 3 |   |    |
 *   |   |   |  G |Y
 * 2 |   | 5 |  r |
 *   |   |   |  a |A
 *   |   |   |  d |x
 *   |   |   |  . |i
 *   |   |   |    |s          X Axis
 *   |   |   v    |-------------------------------
 *   |   |              Grad.
 *   |   v   <---><------------------------------>
 *   |         6                8
 *   | Gap
 *   v<---------------------------------------------------------------> Gap
 *                                    7
 *    <--------------------------------------------------------------------->
 *                                      8
 */

/* #8 */
#define SVG_G_XSIZE	720
/* #6 */
#define SVG_M_XSIZE	70
/* #7 */
#define SVG_V_XSIZE	1050
/* #8 */
#define SVG_T_XSIZE	1060

/* #5 */
#define SVG_G_YSIZE	200
/* #1 */
#define SVG_H_YSIZE	50
/* #4 */
#define SVG_M_YSIZE	50
/* #2 */
#define SVG_T_YSIZE	310
/* #3 */
#define SVG_V_YSIZE	300

/* Grid: Nr of horizontal lines */
#define SVG_H_GRIDNR	3
/* Grid: Nr of vertical lines */
#define SVG_V_GRIDNR	10

/* Block size used to allocate arrays for graphs data */
#define CHUNKSIZE	4096

/* Maximum number of views on a single row */
#define MAX_VIEWS_ON_A_ROW	6

#define SVG_LINE_GRAPH	1
#define SVG_BAR_GRAPH	2

/* Maximum number of horizontal lines for the background grid */
#define MAX_HLINES_NR	10

#define MAYBE	0x80

/*
 ***************************************************************************
 * Macro functions definitions.
 *
 * Note: Using 'do ... while' makes the macros safer to use
 * (remember that macro use is followed by a semicolon).
 ***************************************************************************
 */

/* Close file descriptors */
#define CLOSE_ALL(_fd_)		do {			\
					close(_fd_[0]); \
					close(_fd_[1]); \
				} while (0)

#define CLOSE(_fd_)		if (_fd_ >= 0)		\
					close(_fd_)


/*
 ***************************************************************************
 * Various structure definitions.
 ***************************************************************************
 */

/* Structure for timestamps */
struct tstamp {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int use;
};


/*
 ***************************************************************************
 * Functions prototypes.
 ***************************************************************************
 */

/* Functions used to count number of items */
__nr_t wrap_get_cpu_nr
	(struct activity *);
__nr_t wrap_get_irq_nr
	(struct activity *);
__nr_t wrap_get_serial_nr
	(struct activity *);
__nr_t wrap_get_disk_nr
	(struct activity *);
__nr_t wrap_get_iface_nr
	(struct activity *);
__nr_t wrap_get_fan_nr
	(struct activity *);
__nr_t wrap_get_temp_nr
	(struct activity *);
__nr_t wrap_get_in_nr
	(struct activity *);
__nr_t wrap_get_freq_nr
	(struct activity *);
__nr_t wrap_get_usb_nr
	(struct activity *);
__nr_t wrap_get_filesystem_nr
	(struct activity *);
__nr_t wrap_get_fchost_nr
	(struct activity *);

/* Functions used to read activities statistics */
__read_funct_t wrap_read_stat_cpu
	(struct activity *);
__read_funct_t wrap_read_stat_pcsw
	(struct activity *);
__read_funct_t wrap_read_stat_irq
	(struct activity *);
__read_funct_t wrap_read_swap
	(struct activity *);
__read_funct_t wrap_read_paging
	(struct activity *);
__read_funct_t wrap_read_io
	(struct activity *);
__read_funct_t wrap_read_meminfo
	(struct activity *);
__read_funct_t wrap_read_kernel_tables
	(struct activity *);
__read_funct_t wrap_read_loadavg
	(struct activity *);
__read_funct_t wrap_read_tty_driver_serial
	(struct activity *);
__read_funct_t wrap_read_disk
	(struct activity *);
__read_funct_t wrap_read_net_dev
	(struct activity *);
__read_funct_t wrap_read_net_edev
	(struct activity *);
__read_funct_t wrap_read_net_nfs
	(struct activity *);
__read_funct_t wrap_read_net_nfsd
	(struct activity *);
__read_funct_t wrap_read_net_sock
	(struct activity *);
__read_funct_t wrap_read_net_ip
	(struct activity *);
__read_funct_t wrap_read_net_eip
	(struct activity *);
__read_funct_t wrap_read_net_icmp
	(struct activity *);
__read_funct_t wrap_read_net_eicmp
	(struct activity *);
__read_funct_t wrap_read_net_tcp
	(struct activity *);
__read_funct_t wrap_read_net_etcp
	(struct activity *);
__read_funct_t wrap_read_net_udp
	(struct activity *);
__read_funct_t wrap_read_net_sock6
	(struct activity *);
__read_funct_t wrap_read_net_ip6
	(struct activity *);
__read_funct_t wrap_read_net_eip6
	(struct activity *);
__read_funct_t wrap_read_net_icmp6
	(struct activity *);
__read_funct_t wrap_read_net_eicmp6
	(struct activity *);
__read_funct_t wrap_read_net_udp6
	(struct activity *);
__read_funct_t wrap_read_cpuinfo
	(struct activity *);
__read_funct_t wrap_read_fan
	(struct activity *);
__read_funct_t wrap_read_temp
	(struct activity *);
__read_funct_t wrap_read_in
	(struct activity *);
__read_funct_t wrap_read_meminfo_huge
	(struct activity *);
__read_funct_t wrap_read_time_in_state
	(struct activity *);
__read_funct_t wrap_read_bus_usb_dev
	(struct activity *);
__read_funct_t wrap_read_filesystem
	(struct activity *);
__read_funct_t wrap_read_fchost
	(struct activity *);
__read_funct_t wrap_read_softnet
	(struct activity *);

/* Other functions */
void allocate_bitmaps
	(struct activity * []);
void allocate_structures
	(struct activity * []);
int check_alt_sa_dir
	(char *, int, int);
int check_disk_reg
	(struct activity *, int, int, int);
void check_file_actlst
	(int *, char *, struct activity * [], struct file_magic *, struct file_header *,
	 struct file_activity **, unsigned int [], int, int *, int *);
int check_net_dev_reg
	(struct activity *, int, int, int);
int check_net_edev_reg
	(struct activity *, int, int, int);
double compute_ifutil
	(struct stats_net_dev *, double, double);
void copy_structures
	(struct activity * [], unsigned int [],	struct record_header [], int, int);
int datecmp
	(struct tm *, struct tstamp *);
void display_sa_file_version
	(FILE *, struct file_magic *);
void enum_version_nr
	(struct file_magic *);
void free_bitmaps
	(struct activity * []);
void free_structures
	(struct activity * []);
int get_activity_nr
	(struct activity * [], unsigned int, int);
int get_activity_position
	(struct activity * [], unsigned int, int);
char *get_devname
	(unsigned int, unsigned int, int);
void get_file_timestamp_struct
	(unsigned int, struct tm *, struct file_header *);
void get_itv_value
	(struct record_header *, struct record_header *, unsigned long long *);
void handle_invalid_sa_file
	(int *, struct file_magic *, char *, int);
int next_slice
	(unsigned long long, unsigned long long, int, long);
int parse_sar_opt
	(char * [], int *, struct activity * [], unsigned int *, int);
int parse_sar_I_opt
	(char * [], int *, struct activity * []);
int parse_sa_P_opt
	(char * [], int *, unsigned int *, struct activity * []);
int parse_sar_m_opt
	(char * [], int *, struct activity * []);
int parse_sar_n_opt
	(char * [], int *, struct activity * []);
int parse_timestamp
	(char * [], int *, struct tstamp *, const char *);
void print_report_hdr
	(unsigned int, struct tm *, struct file_header *);
void print_sar_comment
	(int *, int, char *, char *, int, char *, struct file_header *);
__printf_funct_t print_sar_restart
	(int *, int, char *, char *, int, struct file_header *);
int print_special_record
	(struct record_header *, unsigned int, struct tstamp *, struct tstamp *,
	 int, int, struct tm *, struct tm *, char *, int, struct file_magic *,
	 struct file_header *, struct activity * [], struct report_format *, int, int);
void read_file_stat_bunch
	(struct activity * [], int, int, int, struct file_activity *, int, int);
int read_record_hdr
	(int, void *, struct record_header *, struct file_header *, int, int);
__nr_t read_vol_act_structures
	(int, struct activity * [], char *, struct file_magic *, unsigned int, int, int);
int reallocate_vol_act_structures
	(struct activity * [], unsigned int, unsigned int);
void remap_struct
	(unsigned int [], unsigned int [], void *, unsigned int);
void replace_nonprintable_char
	(int, char *);
int sa_fread
	(int, void *, int, int);
int sa_get_record_timestamp_struct
	(unsigned int, struct record_header *, struct tm *, struct tm *);
int sa_open_read_magic
	(int *, char *, struct file_magic *, int, int *);
void select_all_activities
	(struct activity * []);
void select_default_activity
	(struct activity * []);
void set_bitmap
	(unsigned char [], unsigned char, unsigned int);
void set_default_file
	(char *, int, int);
void set_hdr_rectime
	(unsigned int, struct tm *, struct file_header *);
void set_record_timestamp_string
	(unsigned int, struct record_header *, char *, char *, int, struct tm *);
void swap_struct
	(unsigned int [], void *, int);

#endif  /* _SA_H */
