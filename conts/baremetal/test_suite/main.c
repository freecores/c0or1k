/*
 * Main function for all tests
 *
 * Copyright (C) 2009 B Labs Ltd.
 */
#include <l4/api/errno.h>
#include <container.h>
#include <thread.h>
#include <tests.h>
#include <l4lib/macros.h>
#include L4LIB_INC_ARCH(syslib.h)
#include L4LIB_INC_ARCH(syscalls.h)
#include <l4/api/space.h>


int exit_test_thread(void *arg)
{
	while (1)
		;
	//l4_thread_switch(0);
	//l4_exit(5);
	return 0;
}

int exit_test(void)
{
	int ret;
	struct task_ids ids;

	/* Create and run a new thread */
	if ((ret = thread_create(exit_test_thread, 0,
				 TC_SHARE_SPACE | TC_AS_PAGER,
				 &ids)) < 0) {
		printf("Top-level simple_pager creation failed.\n");
		goto out_err;
	} else
		printf("Thread (%d) created successfully.\n", ids.tid);

	// l4_thread_switch(0);

	/* Kill it */
	printf("Killing Thread (%d).\n", ids.tid);
	if ((ret = l4_thread_control(THREAD_DESTROY, &ids)) < 0)
		printf("Error: Killing Thread (%d), err = %d\n", ids.tid, ret);
	else
		printf("Success: Killed Thread (%d)\n", ids.tid);


#if 0
	/* Wait on it */
	printf("Waiting on Thread (%d) to exit.\n", ids.tid);
	if ((ret = l4_thread_control(THREAD_WAIT, &ids)) >= 0)
		printf("Success. Paged child returned %d\n", ret);
	else
		printf("Error. Wait on (%d) failed. err = %d\n",
		       ids.tid, ret);

#endif
	return 0;
out_err:
	BUG();
}

int main(void)
{
	printf("%s: Container %s started\n",
	       __CONTAINER__, __CONTAINER_NAME__);

	capability_test();

	//exit_test();

	/* Now quit to demo self-paging quit */
	//l4_exit(0);

	/* Now quit by null pointer */
	//	*((int *)0) = 5;

	return 0;
}

