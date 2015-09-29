#define SIZE 128
typedef struct istack{
	int i;
	int arr[SIZE];
}istack;

void i_init(istack *s);
void i_push(istack *s, int x);
int i_pop(istack *s);
int i_empty(istack *s);
int i_full(istack *s);
