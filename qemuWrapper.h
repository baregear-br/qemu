#ifndef QEMU_LIB_H
#define QEMU_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Opaque handle for QEMU emulator instance */
typedef struct QEMUContext QEMUContext;

/* Configuration options for QEMU initialization */
typedef struct {
    const char *target_arch;      /* Target architecture (e.g., "x86_64", "arm") */
    const char *qemu_binary;      /* Path to QEMU binary/library */
    int memory_size;              /* Memory size in MB */
    int enable_debug;             /* Enable debug output */
    const char *cpu_model;        /* CPU model string */
} QEMUConfig;

/**
 * Initialize QEMU emulator for a specific architecture
 * 
 * @param config Configuration structure
 * @return QEMU context handle on success, NULL on failure
 */
QEMUContext* qemu_init(const QEMUConfig *config);

/**
 * Execute a target binary with QEMU
 * 
 * @param ctx QEMU context from qemu_init
 * @param argc Argument count
 * @param argv Argument vector (including program name)
 * @param envp Environment variables
 * @return Exit code of the emulated program
 */
int qemu_exec(QEMUContext *ctx, int argc, char **argv, char **envp);

/**
 * Execute a target binary with QEMU (simplified version)
 * 
 * @param ctx QEMU context from qemu_init
 * @param program_path Path to the target executable
 * @param argv Arguments (can be NULL)
 * @return Exit code of the emulated program
 */
int qemu_exec_simple(QEMUContext *ctx, const char *program_path, char **argv);

/**
 * Cleanup and free QEMU context
 * 
 * @param ctx QEMU context to cleanup
 */
void qemu_cleanup(QEMUContext *ctx);

/**
 * Get last error message
 * 
 * @return Error string (valid until next qemu call)
 */
const char* qemu_get_error(void);

/**
 * Set QEMU log level
 * 
 * @param level Log level (0=off, 1=error, 2=warn, 3=info, 4=debug)
 */
void qemu_set_log_level(int level);

#ifdef __cplusplus
}
#endif

#endif /* QEMU_LIB_H */