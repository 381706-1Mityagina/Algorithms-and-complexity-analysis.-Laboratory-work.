//----------------------------------------------//
// ---- EFFECTIVE ALGORITHM with avl trees ---- //
//----------------------------------------------//
#include <iostream>
//#include "segments_generate.cpp"
//#include "line_segment.cpp"

// АВЛ-дерево — сбалансированное по высоте двоичное дерево поиска: для каждой его вершины высота её 
// двух поддеревьев различается не более чем на 1.
// АВЛ — аббревиатура, образованная первыми буквами фамилий создателей (советских учёных) Георгия 
// Максимовича Адельсон-Вельского и Евгения Михайловича Ландиса. 

using namespace std;

int smth = 0;

struct node
{
//    LineSegment line;
    double key;
    int height;
    struct node *left;
    struct node *right;
}* root;

class avlTree
{
    public:
//        node* newNode(double key, LineSegment line);
        node* newNode(double key);
        node* rightRotate(struct node *y);
        node* leftRotate(struct node *x);

        struct node* insert(struct node* node, double key);
        struct node * minValNode(struct node* node);
        struct node* deleteNode(struct node* root, double key);

        void display(node *ptr, int level);
        void preOrder(struct node *root);
        void postOrder(struct node *root);
        void inOrder(struct node *root);
        void search(double);
        void reflect(node * p);
        void defoliate();

        int height(struct node *N);
        int getBalance(struct node *N);
        int max(int a, int b);
};

// -------------------------------------------------------------------------------------------------
void avlTree::search(double key)
{
    node *temp = root, *parent = root;
    if(temp == NULL)
        cout << "\nThe AVL Tree is empty\n" << endl;
    else
    {
        while(temp != NULL && temp->key != key)
        {
            parent = temp;
            if(temp->key < key)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
    }
    
    if(temp == NULL)
        cout << "This element is NOT present in the tree!";
    else
    {
        cout << "\nThis element is present in the tree! ";
        cout << "\nIt's height is: " << temp->height;
    }
}

// -------------------------------------------------------------------------------------------------
// Меняет местами левый и правый узлы, чтобы создать отражение AVL-дерева
void avlTree::reflect(node * p)
{
     if(!p) return;
     reflect(p->left);
     reflect(p->right);
     node * temp = p->left;
     p->left = p->right;
     p->right = temp;
     
}
// -------------------------------------------------------------------------------------------------
void destroy(node *p)
{
     if(!p) return;
     destroy(p->left);
     destroy(p->right);
     delete p;
}

// -------------------------------------------------------------------------------------------------
void d(node *p)
{    
    node* lc = p->left;
     
    if(lc && (lc->left || lc->right)) d(lc);
    else
    { 
       delete lc;
       p->left=NULL;
    }
    node* rc = p->right;
    
    if(rc && (rc->left || rc->right)) d(rc);
    else
    { 
        delete rc;
        p->right=NULL;
    }
}
// -------------------------------------------------------------------------------------------------
// Удаление листьев
void avlTree::defoliate()
{
    if(!root) return;

    if(root->left || root->right) d(root);
    else
       destroy(root);
}

// -------------------------------------------------------------------------------------------------
int avlTree::max(int a, int b)
{
    return (a > b)? a : b;
}
 
// -------------------------------------------------------------------------------------------------
int avlTree::height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// -------------------------------------------------------------------------------------------------
void avlTree::display(node *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        cout << "\n"; 
        if (ptr == root)
        cout << "Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout <<"        ";
        cout << ptr->key;
        display(ptr->left, level + 1);
    }
}
 
// -------------------------------------------------------------------------------------------------
//struct node* avlTree::newNode(double key, LineSegment line)
//{
//    struct node* node = (struct node*)
//                        malloc(sizeof(struct node));
//    node->line = line;
//    node->key = key;
//    node->left = NULL;
//    node->right = NULL;
//    node->height = 1;  // новый узел изначально добавляется в лист
//    return(node);
//}

struct node* avlTree::newNode(double key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // новый узел изначально добавляется в лист
    return(node);
}
 
// -------------------------------------------------------------------------------------------------
// Функция правого поворота поддерева с корнем у
struct node* avlTree::rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
     // Поворот
    x->right = y;
    y->left = T2;
     // Обновление высот
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
     // Новый корень
    return x;
}
 
// -------------------------------------------------------------------------------------------------
// Функция правого поворота поддерева с корнем x
struct node* avlTree::leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}
// -------------------------------------------------------------------------------------------------
// Относительно АВЛ-дерева балансировкой вершины называется операция, которая в случае разницы 
// высот левого и правого поддеревьев = 2, изменяет связи предок-потомок в поддереве данной 
// вершины так, что разница становится <= 1, иначе ничего не меняет. Указанный результат получается 
// вращениями поддерева данной вершины. 

int avlTree::getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// -------------------------------------------------------------------------------------------------
struct node* avlTree::insert(struct node* node, double key)
{
    //Binary Search Tree поворот
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    // Затем мы обновляем высоту этого узла-предка
    node->height = max(height(node->left), height(node->right)) + 1;
    // Коэффициент баланса этого узла-предка, чтобы проверить, не стал ли этот узел несбалансированным
    int balance = getBalance(node);
    // Если этот узел становится несбалансированным, то
    // 1.ЛЛ
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    // 2.ПП
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // 3.ЛП
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    // 4.ПЛ
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}
// -------------------------------------------------------------------------------------------------
struct node * avlTree::minValNode(struct node* node)
{
    struct node* current = node;

    while (current->left != NULL)
        current = current->left;
    return current;
}
 
// -------------------------------------------------------------------------------------------------
struct node* avlTree::deleteNode(struct node* root, double key)
{
    // БДП удаление (бин дер поиска)
    if (root == NULL)
        return root;
    // Если удаляемый ключ меньше, чем корневой ключ, то он лежит в левом поддереве
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    // Если удаляемый ключ больше, чем корневой ключ, он находится в правом поддереве
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else
    {   // нет потомка (правого или левого)
        if( (root->left == NULL) || (root->right == NULL) )
        {   
            struct node *temp = root->left ? root->left : root->right;
            smth=1;
            // Нет детей
            if(temp == NULL)
            {       
                temp = root;
                root = NULL;
                smth=1;
            }
            else // Один ребенок
             {*root = *temp;smth=1;}
        free(temp);
        }
        else
        {   // Узел с двумя детьми: получить самый маленький в правом поддереве
            struct node* temp = minValNode(root->right);
            // Скопируйте данные преемника в этот узел
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    if (root == NULL)
      return root;
    // Обновить высоту текущего узла
    root->height = max(height(root->left), height(root->right)) + 1;
    // Проверить баланс
    int balance = getBalance(root);
    // Если несбалансирован, то
    // 1. ЛЛ
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    // 2. ЛП
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
    // 3. ПП
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    // 4. ПЛ
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
// -------------------------------------------------------------------------------------------------
void avlTree::preOrder(struct node *root)
{
    if(root != NULL)
    {
        cout << root->key; 
        preOrder(root->left);
        preOrder(root->right);
    }
}
// -------------------------------------------------------------------------------------------------
void avlTree::postOrder(struct node *root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key; 
    }
}
// -------------------------------------------------------------------------------------------------
void avlTree::inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        cout << root->key; 
        inOrder(root->right);
    }
}
// -------------------------------------------------------------------------------------------------
