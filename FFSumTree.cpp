#include "common.h"
#include <ff.h>

Value FFSumTree(TreeNode * root){
  if(root->node_count < 1000){
    return SerialSumTree(root);
  }
  else
  {
    Value result = root->value;
    ff::para<> l, r;
    Value x = 0, y = 0;
    if(root->left)
      l([&x, root](){ x = FFSumTree(root->left);});
    if(root->right)
      r([&y, root](){ y = FFSumTree(root->right);});

    return result + (l&&r).then([&x, &y]()->Value{return x+y;});
  }
}
