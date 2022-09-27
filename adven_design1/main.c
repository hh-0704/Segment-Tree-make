#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int* seg_tree_const(int* list, int size) {     /* 주어진 입력 리스트를 세그먼트 트리로 구성하기 위한 전 단계 알고리즘 */
	double temp = size;
	int height = log2(temp);
	int cal = pow(2, height);
	if (cal % size != 0) {
		height += 1;
	}
	int t_size = (pow(2, height + 1)) - 1;
	int *segtree = calloc(t_size, sizeof(int));
	construct_tree(list, 0, size-1, segtree, 0);
	return segtree;
}

int construct_tree(int* list, int start, int end, int* segtree, int cur) {   /* 주어진 입력 리스트를 세그먼트 트리로 구성하는 알고리즘 */
	if (start == end) {
		segtree[cur] = list[start];
		return list[start];
	}
	int mid = start + (end - start) / 2;
	int child = 2 * cur;
	segtree[cur] = construct_tree(list, start, mid, segtree, child + 1) + construct_tree(list, mid + 1, end, segtree, child + 2);
	return segtree[cur];
}

int Getquery(int* segtree, int size, int q_s, int q_e) {    /* 세그먼트 트리를 사용하여 부분 합을 계산하기 위한 전 단계 알고리즘 */
	int sum = 0;
	if (q_s<0 || q_e>size - 1 || q_e < q_s) {
		printf("잘못된 질의 영역 인덱스 선택입니다.\n");
		return 0;
	}
	sum = Querysum(segtree, 0, size - 1, q_s, q_e, 0);
	return sum;
}

int Querysum(int* segtree, int start, int end, int q_s, int q_e, int cur) {    /* 세그먼트 트리를 사용하여 부분 합을 계산하는 알고리즘 */
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

int* Segtree_update(int* segtree, int size, int find, int d_value) {     /* 입력 리스트의 값이 변경되었을 때 세그먼트 트리를 갱신하는 알고리즘 */
	int num = find;
	double temp = size;
	int height = log2(temp);
	int cal = pow(2, height);
	if (cal % size != 0) {
		height += 1;
	}
	int t_size = (pow(2, height + 1)) - 1;
	int find_index = -1;
	for (int i = 0; i < t_size; i++) {
		if (segtree[i] == find) {
			find_index = i;
		}
	}
	while (find_index >= 1) {
		segtree[find_index] += d_value;
		find_index = (find_index - 1) / 2;
	}
	segtree[find_index] += d_value;
	
	return segtree;
}

void print_tree(int* segtree, int size) {      /* 세그먼트 트리완성된 것을 출력을 해보는 알고리즘 */
	double temp = size;
	int height = log2(temp);
	int cal = pow(2, height);
	if (cal % size != 0) {
		height += 1;
	}
	int t_size = (pow(2, height + 1)) - 1;
	int step = 1;
	printf("\n세그먼트 트리의 완성\n");
	for (int i = 0; i < t_size; i++) {
		printf("%d\t", segtree[i]);
		if ((i + 1) == (pow(2, step) - 1)) {
			printf("\n");
			step += 1;
		}
	}
}


void main(void) {      /* 세그먼트 트리의 구현 과제를 실행하여 수행이 잘되는지 확인하기위한 메인함수 */
	int size = 0; 
	printf("입력 리스트의 길이를 정해주세요:");      /* 입력리스트의 길이를 정하는 단계 */
	scanf("%d", &size);
	int *list = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		int temp = 0;
		printf("리스트의 값들을 입력해주세요: ");       /* 입력리스트의 길이가 정해지고 정해진 길이에 맞게 만들어진 입력리스트의 값을 입력하는 단계 */
		scanf("%d", &temp);
		list[i] = temp;
	}

	printf("\n입력받은 리스트의 값\n");    /* 입력받은 입력리스트의 값을 확인차 출력하는 코드 */
	for (int j = 0; j < size; j++) {
		printf("%d\t", list[j]);
	}
	printf("\n");
	
	int* segtree = seg_tree_const(list, size);     /* 세그먼트 트리를 구현하고 메인함수에서 리턴 받는 단계 */
	print_tree(segtree, size);              /* 입력리스트에 대한 세그먼트 트리가 완성된 것을 출력해주는 단계 */

	int choose = 1;
	printf("\n\n세그먼트 트리의 활용 알고리즘입니다.\n");
	while (1) {			/* while문을 활용해 세그먼트 트리의 활용알고리즘 질의 범위의 합을 구하는 알고리즘과 입력리스트의 값을 업데이트 하였을때 세그먼트 트리를 업데이트하는 기능을 확인하는 메뉴를 구현한 부분 */
		printf("\n질의 영역의 합을 구하시려고 한다면 1을\n세그먼트 트리의 값을 업데이트 하신다면 2를\n세그먼트 트리를 출력하려면 3을\n프로그램을 종료하시려면 0을 입력해주세요: ");
		scanf("%d", &choose);
		if (choose == 0)		/* 프로그램 종료 메뉴 */
			break;
		else if (choose == 1) {      /* 질의 영역의 합을 구하는 함수의 메인함수 활용부분 */
			int q_s, q_e;
			printf("질의 영역 시작지점의 인덱스:");   /* 인덱스는 입력리스트의 인덱스를 기반으로 입력을 받는 구조 */
			scanf("%d", &q_s);
			printf("질의 영역 끝지점의 인덱스:");    /* 질의 영역의 합을 구하려는 인덱스의 값을 받아들여 넘겨주는 형식 */
			scanf("%d", &q_e);
			int sum = Getquery(segtree, size, q_s, q_e);
			printf("\n선택하신 질의 영역의 합은: %d 입니다.\n", sum);
		}
		else if (choose == 2) {
			int change, cindex = 0;
			printf("변경하실 값의 인덱스를 입력해주세요: ");   /* 인덱스의 값은 입력리스트를 기준으로 인덱스의 값을 받고 처리함 */
			scanf("%d", &cindex);
			printf("변경하실 값을 입력해주세요: ");      /* 위의 입력리스트 인덱스 값에 업데이트할 값을 입력받는 구조 */
			scanf("%d", &change);
			int d_value = change - list[cindex];
			Segtree_update(segtree, size,list[cindex], d_value);
			list[cindex] = change;
		}
		else if (choose == 3) {    /* 현재 세그먼트 트리의 상태를 출력하는 메뉴 */
			print_tree(segtree, size);
		}
		else {    /* 예외처리 */
			printf("잘못된 값을 입력하셨습니다.");
		}
	}
}