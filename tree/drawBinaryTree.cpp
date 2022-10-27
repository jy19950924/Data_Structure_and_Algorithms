#include <iostream>
#include "./tree.h"
#include <stdlib.h>
#include <string>
#include <deque>

using namespace std;

struct Floor {
    deque<string> lines;
    int width;
    int height;
    int dist;  // 水平距离
    Floor(deque<string> v_lines, int i_width, int i_height, int i_dist)
        : lines(v_lines), width(i_width), height(i_height), dist(i_dist){};
};

Floor *draw(TreeNode *root)
{
    string s_val = to_string(root->val);
    int s_nval = s_val.size();
    if (root->left == nullptr && root->right == nullptr) {

        deque<string> lines = {s_val};
        int width = s_val.size();
        Floor *n_floor = new Floor(lines, width, 1, width / 2);
        return n_floor;

    } else if (root->left == nullptr) {
        Floor *right = draw(root->right);

        string s_nodeFloor = s_val + string(right->dist, '_') + string(right->width - right->dist, '_');
        string s_flagFloor = string(s_nval + right->dist, ' ') + "\\" + string(right->width - right->dist - 1, ' ');
        for (int i = 0; i < right->lines.size(); i++) {
            right->lines[i] = string(s_val.size(), ' ') + right->lines[i];
        }
        right->width += s_nval;
        right->height += 2;
        right->dist = s_nval / 2;
        right->lines.push_front(s_flagFloor);
        right->lines.push_front(s_nodeFloor);
        return right;
    } else if (root->right == nullptr) {
        Floor *left = draw(root->left);

        string s_nodeFloor = string(left->dist + 1, ' ') + string(left->width - left->dist - 1, '_') + s_val;
        string s_flagFloor = string(left->dist, ' ') + "/" + string(left->width - left->dist - 1 + s_nval, ' ');
        for (int i = 0; i < left->lines.size(); i++) {
            left->lines[i] = left->lines[i] + string(s_nval, ' ');
        }
        left->dist = left->width + s_nval / 2;
        left->width = left->width + s_nval;
        left->height += 2;

        left->lines.push_front(s_flagFloor);
        left->lines.push_front(s_nodeFloor);
        return left;
    }
    Floor *left = draw(root->left);
    Floor *right = draw(root->right);
    string s_nodeFloor = string(left->dist + 1, ' ') + string(left->width - left->dist - 1, '_') + s_val +
                         string(right->dist, '_') + string(right->width - right->dist, ' ');
    string s_flagFloor = string(left->dist, ' ') + "/" + string(left->width - left->dist - 1, ' ') +
                         string(s_nval, ' ') + string(right->dist, ' ') + "\\" +
                         string(right->width - right->dist - 1, ' ');
    int index = 0;
    while (index < left->lines.size()) {
        if (index < right->lines.size())
            left->lines[index] = left->lines[index] + string(s_nval, ' ') + right->lines[index];
        else
            left->lines[index] += string(s_nval, ' ') + string(right->width, ' ');
        index++;
    }
    string s_spaceLeft = string(left->width, ' ');
    while (index < right->lines.size()) {
        left->lines.push_back(s_spaceLeft + string(s_nval, ' ') + right->lines[index]);
        index++;
    }
    left->dist = left->width + (s_nval) / 2;
    left->width = left->width + s_nval + right->width;
    left->height = left->height > right->height ? (left->height + 2) : (right->height + 2);

    left->lines.push_front(s_flagFloor);
    left->lines.push_front(s_nodeFloor);
    return left;
}

int main()
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 4, 3};
    int len = sizeof(data) / sizeof(int);

    Tree *ptree = new Tree(data, len);
    Floor *floor = draw(ptree->root);
    for (int i = 0; i < floor->lines.size(); i++) {
        cout << floor->lines[i] << endl;
    }
    return 0;