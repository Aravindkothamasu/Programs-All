#include "Huffman_Header.h"
#define MAX_TREE_HT 100
extern as_data_t CountData[0x7f+1];

struct MinHeapNode* newNode(char data, unsigned freq)
{
  struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
      sizeof(struct MinHeapNode));

  temp->left = temp->right = NULL;
  temp->data = data;
  temp->freq = freq;

  return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)
{
  struct MinHeap* minHeap
    = (struct MinHeap*)malloc(sizeof(struct MinHeap));

  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (struct MinHeapNode**)malloc(
      minHeap->capacity * sizeof(struct MinHeapNode*));
  return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,  struct MinHeapNode** b)
{
  struct MinHeapNode* t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{

  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size
      && minHeap->array[left]->freq
      < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size
      && minHeap->array[right]->freq
      < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != idx) {
    swapMinHeapNode(&minHeap->array[smallest],
	&minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(struct MinHeap* minHeap)
{
  return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{

  struct MinHeapNode* temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i
      && minHeapNode->freq
      < minHeap->array[(i - 1) / 2]->freq) {

    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }

  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)
{

  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);

  printf("\n");
}

int isLeaf(struct MinHeapNode* root)
{
  return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap( int StartIndex)
{
  struct MinHeap* minHeap = createMinHeap ( CAL_SIZE(StartIndex) );

  for (int i = StartIndex; i <= TOT_CHARS; ++i)
    minHeap->array[i-StartIndex] = newNode(CountData[i].Type, CountData[i].Freq );

  minHeap->size = CAL_SIZE(StartIndex);
  buildMinHeap(minHeap);

  return minHeap;
}

void printCodes(struct MinHeapNode* root, int arr[], int top,int StartIndex)
{
  if (root->left)
  {
    arr[top] = 0;
    printCodes(root->left, arr, top + 1, StartIndex);
  }

  if (root->right)
  {
    arr[top] = 1;
    printCodes(root->right, arr, top + 1, StartIndex);
  }

  if (isLeaf(root))
  {
    printf("%3d %c: ", root->data, root->data);
    for ( int i = StartIndex; i<=0x7f;i++)
      if ( CountData[i].Type == root->data )
	CountData[i].top = top;
    printArr(arr, top);
  }
}

struct MinHeapNode *  HuffmanCodes( int StartIndex ) 
{

  struct MinHeapNode *left, *right, *top;
  struct MinHeapNode *root;

  struct MinHeap* minHeap
    = createAndBuildMinHeap( StartIndex);

  while (!isSizeOne(minHeap)) 
  {
    left = extractMin(minHeap);
    right = extractMin(minHeap);

    top = newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    insertMinHeap(minHeap, top);
  }

  root = extractMin(minHeap);

  int arr[MAX_TREE_HT], Itop = 0;

  printCodes(root, arr, Itop, StartIndex);
  return root;
}

#if 0
int main()
{

  char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' ,'g','h','j','k','l','m','n'};
  int freq[]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14};

  int size = sizeof(arr) / sizeof(arr[0]);
  struct MinHeapNode * root;

  root = HuffmanCodes(arr, freq, size);
  return 0;
}
#endif
