/*
   In this programming problem and the next you'll code up the greedy algorithms 
   from lecture for minimizing the weighted sum of completion times..

   This file describes a set of jobs with positive and integral weights and lengths. 
   It has the format

   [number_of_jobs]

   [job_1_weight] [job_1_length]

   [job_2_weight] [job_2_length]

   ...

   For example, the third line of the file is "74 59", indicating that the second 
   job has weight 74 and length 59.

   You should NOT assume that edge weights or lengths are distinct.

   Your task in this problem is to run the greedy algorithm that schedules jobs in 
   decreasing order of the difference (weight - length). Recall from lecture that 
   this algorithm is not always optimal. IMPORTANT: if two jobs have equal difference 
   (weight - length), you should schedule the job with higher weight first. 

Beware: if you break ties in a different way, you are likely to get the wrong answer. 
You should report the sum of weighted completion times of the resulting 
schedule --- a positive integer --- in the box below.

ADVICE: If you get the wrong answer, try out some small test cases to debug your 
algorithm (and post your test cases to the discussion forum).
*/

/* 
   part 2
   For this problem, use the same data set as in the previous problem.

   Your task now is to run the greedy algorithm that schedules jobs (
   optimally) in decreasing order of the ratio (weight/length). 
   In this algorithm, it does not matter how you break ties. 
   You should report the sum of weighted completion times of the 
   resulting schedule --- a positive integer --- in the box below.
   */

#include <stdio.h>
#include <stdlib.h>

typedef struct job {
	long int weight;
	long int length;
	long int diff;
	double ratio;
} job_t;

static int
comp_job_ratio(void const *p1, void const *p2) {
	job_t *j1 = (job_t *)p1;
	job_t *j2 = (job_t *)p2;

	double ret = j2->ratio - j1->ratio;
	if (ret < 0)
		return -1;
	if (ret > 0)
		return 1;
	return 0;
}
static int
comp_job_diff(void const *p1, void const *p2) {
	job_t *j1 = (job_t *)p1;
	job_t *j2 = (job_t *)p2;

	int ret = (j2->diff - j1->diff);
	if (ret == 0)
		ret = j2->weight - j1->weight;
	
	return ret;
}

int main() {
	FILE *fp = fopen("jobs.txt", "r");
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}

	char *line = NULL;;
	size_t len = 0;
	ssize_t read = 0;
	int num;

	read = getline(&line, &len, fp);
	sscanf(line, "%d", &num);
	printf("Number of job: %d\n", num);
	job_t *jobs = calloc(num, sizeof(job_t));
	int i = 0;
	while((read = getline(&line, &len, fp)) != -1) {
		sscanf(line, "%ld %ld", &(jobs[i].weight), &(jobs[i].length));
		jobs[i].diff = jobs[i].weight - jobs[i].length;
		jobs[i].ratio = (double) jobs[i].weight / jobs[i].length;
		i++;
	}
	
	long int completion_time = 0;
	long int c_time = 0;

	qsort(jobs, num, sizeof(job_t), comp_job_diff);
	for (int i = 0; i < 10; i++)
		printf("w[%d]: %ld	l[%d]: %ld	diff: %ld	ratio: %f\n",
				i, jobs[i].weight, i, jobs[i].length, jobs[i].diff, jobs[i].ratio);
	
	for (int i = 0; i < num; i++) {
		c_time += jobs[i].length;
		completion_time += (jobs[i].weight * c_time);
	}
	printf("Weighted completion time: %ld\n", completion_time);
	
	completion_time = 0;
	c_time = 0;
	qsort(jobs, num, sizeof(job_t), comp_job_ratio);
	for (int i = 0; i < 10; i++) {
		c_time += jobs[i].length;
		completion_time += (jobs[i].weight * c_time);
		printf("w[%5d]: %ld	l[%5d]: %ld	diff: %8ld	ratio: %f c_time: %ld, w_time: %ld\n",
				i, jobs[i].weight, i, jobs[i].length, jobs[i].diff, jobs[i].ratio, c_time, completion_time);
	}

	completion_time = 0;
	c_time = 0;
	for (int i = 0; i < num; i++) {
		c_time += jobs[i].length;
		completion_time += (jobs[i].weight * c_time);
	}
	printf("Weighted completion time: %ld\n", completion_time);

	free(jobs);
	free(line);
	fclose(fp);
}
