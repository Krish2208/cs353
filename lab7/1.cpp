#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void lru(string pages, int num_frames)
{
    unordered_set<int> frames;  // Stores the pages in the frames
    unordered_map<int, int> indexes;    // Stores the index of the page in the string
    int faults = 0; // Stores the number of page faults

    int page_id = -1;   // Stores the page id (current)
    int j = 0;  // Starting index of current page in pages string
    for (int i = 0; i < pages.length(); i++)
    {
        if (pages[i] == ',')
        {
            page_id = stoi(pages.substr(j, i - j));     // Get the page id
            if (frames.size() < num_frames)             // If frames are not full
            {
                if (frames.find(page_id) == frames.end())   // If page is not present in frames
                {
                    frames.insert(page_id);         // Insert page in frames
                    indexes[page_id] = i;           // Set index of page in string
                    faults++;                       // Increment number of faults
                }
                else
                {
                    frames.erase(page_id);          // Remove the old page from frames
                    frames.insert(page_id);         // Insert page in frames
                    indexes[page_id] = i;           // Set index of page in string
                }
            }
            else
            {
                if (frames.find(page_id) == frames.end())       // If page is not present in frames
                {                                               
                    int lru = INT_MAX, val;                     
                    for (auto it = frames.begin(); it != frames.end(); it++)    
                    {
                        if (indexes[*it] < lru)
                        {
                            lru = indexes[*it];
                            val = *it;
                        }
                    }
                    frames.erase(val);                          // Remove the least recently used page
                    frames.insert(page_id);                     // Insert page in frames
                    indexes[page_id] = i;                       // Set index of page in string
                    faults++;                                   // Increment number of faults
                }
                else
                {
                    frames.erase(page_id);
                    frames.insert(page_id);
                    indexes[page_id] = i;
                }
            }
            j = i + 1;
        }
        else if (i == pages.length() - 1)
        {
            page_id = stoi(pages.substr(j, i - j + 1));
            if (frames.size() < num_frames)
            {
                if (frames.find(page_id) == frames.end())
                {
                    frames.insert(page_id);
                    indexes[page_id] = i;
                    faults++;
                }
                else
                {
                    frames.erase(page_id);
                    frames.insert(page_id);
                    indexes[page_id] = i;
                }
            }
            else
            {
                if (frames.find(page_id) == frames.end())
                {
                    int lru = INT_MAX, val;
                    for (auto it = frames.begin(); it != frames.end(); it++)
                    {
                        if (indexes[*it] < lru)
                        {
                            lru = indexes[*it];
                            val = *it;
                        }
                    }
                    frames.erase(val);
                    frames.insert(page_id);
                    indexes[page_id] = i;
                    faults++;
                }
                else
                {
                    frames.erase(page_id);
                    frames.insert(page_id);
                    indexes[page_id] = i;
                }
            }
        }
        else
        {
            continue;
        }
    }
    cout << "LRU: ";
    for (auto it = frames.begin(); it != frames.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "Number of faults: " << faults << endl;
    cout << endl;
}

int main()
{
    int num_frames;
    cout << "Enter number of frames: ";
    cin >> num_frames;

    string pages;
    cout << "Enter pages (Separated by comma): ";
    cin >> pages;

    lru(pages, num_frames);

    return 0;
}