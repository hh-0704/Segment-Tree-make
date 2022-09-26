#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int* seg_tree_const(int* list, int size) {
	double temp = size;
	int height = 0;
	while (temp >= 2) {
		temp = temp / 2;
		height += 1;
	}
	height += 1;
	int t_size = (pow(2, height + 1)) - 1;
	int *segtree = calloc(t_size, sizeof(int));
	construct_tree(list, 0, size-1, segtree, 0);
	return segtree;
}

int construct_tree(int* list, int start, int end, int* segtree, int cur) {
	if (start == end) {
		segtree[cur] = list[start];
		return list[start];
	}
	int mid = start + (end - start) / 2;
	int child = 2 * cur;
	segtree[cur] = construct_tree(list, start, mid, segtree, child + 1) + construct_tree(list, mid + 1, end, segtree, child + 2);
	return segtree[cur];
}

int Getquery(int* segtree, int size, int q_s, int q_e) {
	int sum = 0;
	if (q_s<0 || q_e>size - 1 || q_e < q_s) {
		printf("잘못된 질의 영역 인덱스 선택입니다.\n");
		return 0;
	}
	sum = Querysum(segtree, 0, size - 1, q_s, q_e, 0);
	return sum;
}

int Querysum(int* segtree, int start, int end, int q_s, int q_e, int cur) {
	if (q_s <= start && q_e >= end) {
		return segtree[cur];
	}
	if (end < q_s || start > q_e) {
		return 0;
	}
	int mid = start + (end - start) / 2;
	int child = 2 * cur;
	return Querysum(segtree, start, mid, q_s, q_e, child + 1) + Querysum(segtree, mid + 1, end, q_s, q_e, child + 2);
}

int* Segtree_update(int* segtree, int start, int end, int i, int d_value, int cur) {
	if (i<start || i>end) {
		return NULL;
	}
	segtree[cur] = segtree[cur] + d_value;
	if (start != end) {
		int mid = start + (end - start) / 2;
		int child = 2 * cur;
		Segtree_update(segtree, start, mid, i, d_value, child + 1);
		Segtree_update(segtree, mid + 1, end, i, d_value, child + 2);
	}
}

int print_tree(int* segtree, int size) {
	int height = 0;
	while (size >= 2) {
		size = size / 2;
		height += 1;
	}
	height += 1;
	int t_size = (pow(2, height + 1)) - 1;
	printf("\n세그먼트 트리의 완성\n");
	for (int i = 0; i < t_size; i++) {
		printf("%d\t", segtree[i]);
	}
	return t_size;
}


void main(void) {
	int size = 0;
	printf("세그먼트 트리의 길이를 정해주세요:");
	scanf("%d", &size);
	int *list = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		int temp = 0;
		printf("리스트의 값들을 입력해주세요: ");
		scanf("%d", &temp);
		list[i] = temp;
	}

	printf("\n입력받은 리스트의 값\n");
	for (int j = 0; j < size; j++) {
		printf("%d\t", list[j]);
	}
	printf("\n");
	
	int* segtree = seg_tree_const(list, size);
	int seg_size = print_tree(segtree, size);

	int choose = 1;
	printf("\n\n세그먼트 트리의 활용 알고리즘입니다.\n");
	while (1) {
		printf("\n질의 영역의 합을 구하시려고 한다면 1을\n세그먼트 트리의 값을 업데이트 하신다면 2를\n세그먼트 트리를 출력하려면 3을\n프로그램을 종료하시려면 0을 입력해주세요: ");
		scanf("%d", &choose);
		if (choose == 0)
			break;
		else if (choose == 1) {
			int q_s, q_e;
			printf("질의 영역 시작지점의 인덱스:");
			scanf("%d", &q_s);
			printf("질의 영역 끝지점의 인덱스:");
			scanf("%d", &q_e);
			int sum = Getquery(segtree, size, q_s, q_e);
			printf("선택하신 질의 영역의 합은: %d 입니다.\n", sum);
		}
		else if (choose == 2) {
			int change, cindex = 0;
			printf("변경하실 값의 인덱스를 입력해주세요: ");
			scanf("%d", &cindex);
			printf("변경하실 값을 입력해주세요: ");
			scanf("%d", &change);
			int d_value = change - list[cindex];
			list[cindex] = change;
			Segtree_update(segtree, 0, size, cindex, d_value, 0);
		}
		else if (choose == 3) {
			print_tree(segtree, size);
		}
		else {
			printf("잘못된 값을 입력하셨습니다.");
		}
	}
}