#ifndef yaml_data
#define yaml_data

#ifndef yaml_common
#include "common.h"
#endif

/* What type of OS are we running? 32-bit, 64-bit? */
enum os_type
{
	bit32,
	bit64
};

/* Outline of what the yaml file should look like, for our use case only. */
typedef struct yaml_os_data
{
	uint8			n_section;				// 'n'

	// 'n' section
	uint8			pad1;					// 0
	uint8			type;					// 2 = 32bit, 3 = 64bit
	uint8			desc_start;				// 'f'
	uint8			pad2;					// 0

	// Description of second stage bootloader
	uint8			ss_tag;					// 's'(second stage)
	int16			ss_size;				// second stage source code file size
	uint8			pad3;					// 0
	uint8			*ss_filename;			// second stage source code file name
	uint8			pad4;					// 0
	uint16			ss_filename_bin_size;	// second stage binary file name size
	uint8			pad5;					// 0
	uint8			*ss_filename_bin_name;	// second stage binary file name
	uint8			pad6;					// 0
	size			ss_bin_size;			// size(in bytes) of binary file

	// Description of kernel
	uint8			kern_tag;				// 'k'(kernel)
	uint16			kern_filename_size;		// kernel source code file size
	uint8			pad7;					// 0
	uint8			*kern_filename;			// kernel source code file name
	uint8			pad8;					// 0
	uint16			kern_filename_bin_size;	// kernel binary file name size
	uint8			pad9;					// 0
	uint8			*kern_filename_bin_name;// kernel binary file name
	uint8			pad10;					// 0
	size			kern_bin_size;			// size(in bytes) of binary file
} _yaml_os_data;

/* All of the things the yaml file needs to have. Everything else is extra. */
static const char * const needed_names[] = {
	// Type of os. 32bit or 64bit
	"os_type",

	// Second stage information
	"second_stage_binary",
	"second_stage_addr",
	"second_stage_source_code_file",

	// Kernel information
	"kernel_binary",
	"kernel_addr",
	"kernel_source_code_file"
};

/* Types of data. */
enum data_types
{
	Chr,
	Hex,
	Dec,
	Str
};

/* Information about the yaml file, such as user-defined variables/variable data, arrays etc. */
typedef struct data
{
	/* User-defined value. */
	uint8		*user_defined;

	/* Type of information we're storing. */
	enum data_types	data_type;

	/* The value will either be a character, string or decimal/hex. */
	uint16		*val_data;
	
	/* Next user-defined value. */
	struct data	*next;
	
	/* Previous data. */
	struct data	*previous;
} _data;

/* Static reference to yaml file data. */
static _data		*yaml_file_data		= NULL;

/* Reference to first index of yaml_file_data. */
static _data		*all_yaml_data		= NULL;

/* How much data? */
static size		yaml_file_data_size 	= 0;

/* Useful macros :) */
#define _next yaml_file_data = yaml_file_data->next;
#define _back yaml_file_data = yaml_file_data->previous;

/* Initialize memory for yaml file data. */
void init_yaml_data();

/* Assign new data. */
void new_yaml_data(uint8 *user_def, uint16 *data, enum data_types type);

/* Write all the data as binary. */
bool write_binary_file(const uint8 *path);

#endif