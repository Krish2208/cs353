#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void efficient_page_replacement(string pages, int num_frames)
{
    int faults = 0;         // Stores the number of page faults
    unordered_set<int> frames;          // Stores the pages in the frames

    vector<int> pages_list;             // Stores the pages in the order of their arrival
    int j = 0;                          // Starting index of current page in pages string
    int page_id = 0;                    // Stores the page id (current)
    for (int i = 0; i < pages.length(); i++)    // Get the pages from the string
    {
        if (pages[i] == ',')                    // If comma is encountered
        {
            page_id = stoi(pages.substr(j, i - j));         // Get the page id
            pages_list.push_back(page_id);                  // Push the page id in the list
            j = i + 1;                                      // Set the starting index of next page
        }
        else if (i == pages.length() - 1){                  // If last page is encountered
            page_id = stoi(pages.substr(j, i - j + 1));     // Get the page id
            pages_list.push_back(page_id);                  // Push the page id in the list 
        }
    }

    for(int i = 0; i < pages_list.size(); i++)
    {
        if (frames.find(pages_list[i]) == frames.end())     // If page is not present in frames
        {
            if (frames.size() < num_frames)                // If frames are not full
            {
                frames.insert(pages_list[i]);               // Insert page in frames
                faults++;                                   // Increment number of faults
            }
            else
            {
                int last = -1, elementToReplace = -1;           // Stores the index of last occurence of page in pages_list
                for(auto it: frames){                           // Find the page which will be used last
                    int k;                                      // Stores the index of last occurence of page in pages_list
                    for(k = i+1; k < pages_list.size(); k++)        // Find the index of last occurence of page in pages_list
                    {                                               
                        if(it == pages_list[k]){                    // If page is found
                            if(k>last){                             // If index is greater than last
                                last = k;                           // Set last to index
                                elementToReplace = it;              // Set elementToReplace to page
                            }
                            break;                                  // Break the loop
                        }
                    }
                    if(k == pages_list.size()){                    // If page is not found
                        elementToReplace = it;                      // Set elementToReplace to page
                        break;                                      // Break the loop
                    }
                }
                if (last == -1) frames.erase(frames.begin());       // If page is not found in pages_list, remove the first page
                else frames.erase(elementToReplace);                // Else remove the page which will be used last
                frames.insert(pages_list[i]);                   // Insert page in frames
                faults++;                                       // Increment number of faults
            }
        }
    }
    cout << "Effective Page Replacement: ";
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

    efficient_page_replacement(pages, num_frames);

    return 0;
}