#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#define DIGITSIZE 100
#define BUCKETSIZE 10
#define MAXSIZE 10000
#define MAXLINE 100
#define BUCLETSORT 1
#define MERGESORT 0

// 成绩节点
typedef struct Score {
	int total;
	int total_big3;
	int yw;
	int sx;
	int yy;
	int wl;
	int hx;
	int sw;
	int ls;
	int dl;
	int zz;
}ScoreList;

// 桶链表节点
struct ListNode {
	struct Score score;
	struct ListNode *next;
};

// 桶头节点
struct Bucket {
	struct ListNode *head;
};

// 取指定位数上的值
int getDigitValue(int number, int pos) {
	while (pos > 1) {
		number = number / 10;
		pos--;
	}
	number %= 10;
	return number;
}

// 初始化桶：为每一个桶分配空间，头节点取空
void initializeBuckets(struct Bucket **buckets, int bucketSize) {
	int i;
	for (i = 0; i < bucketSize; i++) {
		buckets[i] = malloc(sizeof(struct Bucket));
		buckets[i]->head = NULL;
	}
}

// 向指定 position 的桶中添加节点
void addToBucket(struct Bucket **buckets, struct Score item, int position) {
	struct Bucket *bucket = buckets[position];
	struct ListNode *newNode = malloc(sizeof(struct ListNode));
	newNode->score = item;
	newNode->next = NULL;
    //桶内从头节点开始从小到大排序
	if (bucket->head) {
		struct ListNode *current = bucket->head;
		struct ListNode *prev = NULL;
		while (current) {
			// 根据关键字优先级选择插入位置
			if (current->score.total > item.total ||
				(current->score.total == item.total && current->score.total_big3 > item.total_big3) ||
				(current->score.total == item.total && current->score.total_big3 == item.total_big3 && current->score.yw > item.yw) ||
                (current->score.total == item.total && current->score.total_big3 == item.total_big3 && current->score.yw == item.yw && current->score.sx > item.sx) ||
                (current->score.total == item.total && current->score.total_big3 == item.total_big3 && current->score.yw == item.yw && current->score.sx == item.sx && current->score.yy >= item.yy)) {
				newNode->next = current;
				if (prev) {
					prev->next = newNode;
				} else {
					bucket->head = newNode;
				}
				break;
			}
			prev = current;
			current = current->next;
		}
		if (!current) {
			prev->next = newNode;
		}
	} else {
		bucket->head = newNode;
	}
}

// 根据指定数位 pos 向桶中添加节点
void addToBucketByDigit(struct Bucket **buckets, struct Score item, int pos) {
	int digitValue = getDigitValue(item.total, pos);
	addToBucket(buckets, item, digitValue);
}

// 遍历桶，将数据取出
void scanBucket(struct Bucket **buckets, struct Score *data, int bucketSize) {
	int sp = -1, i;
	struct ListNode *listNode;
	for (i = 0; i < bucketSize; i++) {
		listNode = buckets[i]->head;
		while (listNode) {
			data[++sp] = listNode->score;
			listNode = listNode->next;
		}
	}
}

// 桶排序
void bucketSort(struct Score *data, int size, int pos) {
	struct Bucket *buckets[BUCKETSIZE];
	initializeBuckets(buckets, BUCKETSIZE);
	int i;
	for (i = 0; i < size; i++)
		addToBucketByDigit(buckets, data[i], pos);
	scanBucket(buckets, data, BUCKETSIZE);//先分配，再收集
}

// 基数排序
void radixSort(struct Score *data, int size, int digitSize) {
	int i;
	for (i = 1; i <= digitSize; i++)
		bucketSort(data, size, i);
}

// 合并两个有序数组
void merge(struct Score *data, int head, int mid, int rear) {
	int i = head, j = mid, k = 0;
	struct Score *temp = malloc((rear - head) * sizeof(struct Score));

	while (i < mid && j < rear) {
		// 根据关键字优先级选择合并
		if (data[i].total < data[j].total ||
			(data[i].total == data[j].total && data[i].total_big3 < data[j].total_big3) ||
			(data[i].total == data[j].total && data[i].total_big3 == data[j].total_big3 && data[i].yw < data[j].yw) ||
            (data[i].total == data[j].total && data[i].total_big3 == data[j].total_big3 && data[i].yw == data[j].yw && data[i].sx < data[j].sx) ||
            (data[i].total == data[j].total && data[i].total_big3 == data[j].total_big3 && data[i].yw == data[j].yw && data[i].sx == data[j].sx && data[i].yy <= data[j].yy)) {
			temp[k++] = data[i++];
		} else {
			temp[k++] = data[j++];
		}
	}

	while (i < mid) {
		temp[k++] = data[i++];
	}

	while (j < rear) {
		temp[k++] = data[j++];
	}

	for (i = 0; i < k; i++) {
		data[head + i] = temp[i];
	}

	free(temp);
}

// 归并排序
void mergeSort(struct Score *data, int head, int rear) {
	if (head >= rear - 1)
		return;
    //递归实现
	int mid = (head + rear) / 2;
	mergeSort(data, head, mid);
	mergeSort(data, mid, rear);
	merge(data, head, mid, rear);
}


// 打印排序结果
void displayOutcome(struct Score *data, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("Total: %d, Total_Big3: %d, Yw: %d, Sx: %d, Yy: %d, Wl: %d, Hx: %d, Sw: %d, Ls: %d, Dl: %d, Zz: %d\n",
			data[i].total, data[i].total_big3, data[i].yw, data[i].sx, data[i].yy, data[i].wl, data[i].hx, data[i].sw, data[i].ls, data[i].dl, data[i].zz);
	}
	printf("\n");
}

//将csv文件读入，并返回关键字数
int ReadFile(ScoreList *data){
	FILE *fp = fopen("example.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
	printf("read file success!\n");
	char row[MAXLINE];
	char *token;
	int i;
	int cnt;//关键字数
	
	cnt = 0;
	fgets(row, MAXLINE, fp);//忽略标题行，因为标题暂时已经固定了
	token = strtok(row, ",");
	while (token != NULL) {
		token = strtok(NULL, ",");
		cnt++;
	}
	printf("num of keywords:%d\n\n", cnt);
	i = 0;
	while (fgets(row, MAXLINE, fp) != NULL){
		token = strtok(row, ",");
		//根据关键字数给data数组赋值
		switch (cnt)
		{
		case 6:
			data[i].total = atoi(token);
			token = strtok(NULL, ",");
			data[i].total_big3 = atoi(token);
			token = strtok(NULL, ",");
			data[i].yw = atoi(token);
			token = strtok(NULL, ",");
			data[i].sx = atoi(token);
			token = strtok(NULL, ",");
			data[i].yy = atoi(token);
			token = strtok(NULL, ",");
			data[i].wl = atoi(token);
			break;
		case 5:
			data[i].total_big3 = atoi(token);
			token = strtok(NULL, ",");
			data[i].yw = atoi(token);
			token = strtok(NULL, ",");
			data[i].sx = atoi(token);
			token = strtok(NULL, ",");
			data[i].yy = atoi(token);
			token = strtok(NULL, ",");
			data[i].wl = atoi(token);
			break;
		case 4:
			data[i].yw = atoi(token);
			token = strtok(NULL, ",");
			data[i].sx = atoi(token);
			token = strtok(NULL, ",");
			data[i].yy = atoi(token);
			token = strtok(NULL, ",");
			data[i].wl = atoi(token);
			break;
		case 3:
			data[i].sx = atoi(token);
			token = strtok(NULL, ",");
			data[i].yy = atoi(token);
			token = strtok(NULL, ",");
			data[i].wl = atoi(token);
			break;
		case 2:
			data[i].yy = atoi(token);
			token = strtok(NULL, ",");
			data[i].wl = atoi(token);
			break;
		case 1:
			data[i].wl = atoi(token);
			break;
		
		default:
			break;
		}
		i++;
    }

	fclose(fp);
	return cnt;
}

//将data数组写入csv文件中，返回写入的数据量
int WriteFile(struct Score *data, int cnt, int size){
	FILE *fp = fopen("new3.csv", "w+");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }

	//打印表头
	switch (cnt)
	{
	case 6:
		fprintf(fp, "total,");
	case 5:
		fprintf(fp, "total_big3,");
	case 4:
		fprintf(fp, "yw,");
	case 3:
		fprintf(fp, "sx,");
	case 2:
		fprintf(fp, "yy,");
	case 1:
		fprintf(fp, "wl\n");
		break;
	
	default:
		break;
	}

	//打印表项
	int i, j;
	int data_cnt = 0;
	for(i = 0; i < size; i++){//行
		if(!data[i].wl && !data[i].yy && !data[i].sx && !data[i].yw)continue;//跳过全0项
		switch (cnt)
		{
		case 6:
			fprintf(fp, "%d,", data[i].total);
		case 5:
			fprintf(fp, "%d,", data[i].total_big3);
		case 4:
			fprintf(fp, "%d,", data[i].yw);
		case 3:
			fprintf(fp, "%d,", data[i].sx);
		case 2:
			fprintf(fp, "%d,", data[i].yy);
		case 1:
			fprintf(fp, "%d\n", data[i].wl);
			break;
		
		default:
			break;
		}
		data_cnt++;
	}
	fclose(fp);
	return data_cnt;
}

int main() {
	// struct Score data[] = {
	// 	{300, 240, 70, 80, 90, 60},
	// 	{270, 210, 60, 70, 80, 60},
	// 	{300, 240, 80, 75, 85, 60},
	// 	{315, 255, 85, 95, 75, 60},
	// 	{280, 220, 75, 65, 80, 60}
	// };

	//title
	printf("\tMulti keyword sorting\n\n");
	printf("=====================================\n");
	//成绩数组定义、初始化
	ScoreList data[MAXSIZE] = {0};
	int cnt;
	cnt = ReadFile(data);
	int size = sizeof(data) / sizeof(struct Score);
	clock_t test;

	//排序
	int sortStrategy;
	clock_t start, end;
	printf("*Please select sort strategy*\n");
	printf("Enter 1 to use Bucket sort+Radix sort, and enter 0 to use Merge sort:\n");
	// scanf("%d", &sortStrategy);
	char c;
	while((c = getchar()) != '\n'){
		if(c == '0' || c == '1'){
			sortStrategy = c - '0';
			break;
		}else{
			while((c = getchar()) != '\n');
			printf("Illegal input, please re-enter\n");
			printf("Enter 1 to use Bucket sort+Radix sort, and enter 0 to use Merge sort:\n");
		}
	}
	printf("\n");
	if(sortStrategy == BUCLETSORT){
		start = clock();
		radixSort(data, size, 3);
		end = clock();
		// displayOutcome(data, size);
		printf("*Sorting complete.Please check sorted.csv in the current directory.*\nBucketSort+RadixSort, time:%8.2fms\n", (double)(end-start));
	}else if(sortStrategy == MERGESORT){
		start = clock();
		mergeSort(data, 0, size);
		end = clock();
		// displayOutcome(data, size);
		printf("Sorting complete.Please check sorted.csv in the current directory.*\nMergeSort, time:%8.2fms\n", (double)(end-start));
	}

	//写文件
	int data_cnt;
	data_cnt = WriteFile(data, cnt, size);
	printf("%d group of data sorted\n", data_cnt);
	// displayOutcome(data, size);
	system("pause");
	return 0;
}