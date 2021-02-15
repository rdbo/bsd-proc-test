#include <stdio.h>
#include <stdlib.h>
#include <kvm.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/user.h>
#include <libprocstat.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <paths.h>

int main()
{
	kvm_t *kd = kvm_openfiles(NULL, _PATH_DEVNULL, NULL, O_RDONLY, NULL);
	int proc_count = 0;
	struct kinfo_proc *procs = kvm_getprocs(kd, KERN_PROC_PROC, 0, &proc_count);
	kvm_close(kd);
	int proc_num = 0;
	struct procstat *ps = procstat_open_sysctl();
	for(proc_num = 0; proc_num < proc_count; ++proc_num)
	{
		char proc_path[PATH_MAX] = {0};
		procstat_getpathname(ps, &procs[proc_num], proc_path, sizeof(proc_path));
		printf("Process ID:   %i\n", procs[proc_num].ki_pid);
		printf("Process Name: %s\n", procs[proc_num].ki_comm);
		printf("Process Path: %s\n", proc_path);
		printf("--------------------\n");
	}
	procstat_close(ps);
	free(procs);
	return 0;
}
