#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int main() {
    int reference_string[MAX_PAGES];
    int page_frames[MAX_FRAMES];
    int page_faults = 0;
    int future_index[MAX_FRAMES][MAX_PAGES];
    
    printf("Enter the reference string (sequence of page numbers): ");
    for (int i = 0; i < MAX_PAGES; i++) {
        scanf("%d", &reference_string[i]);
    }

    for (int i = 0; i < MAX_FRAMES; i++) {
        page_frames[i] = -1;
    }

    for (int i = 0; i < MAX_FRAMES; i++) {
        for (int j = 0; j < MAX_PAGES; j++) {
            future_index[i][j] = MAX_PAGES;
            for (int k = j + 1; k < MAX_PAGES; k++) {
                if (reference_string[k] == page_frames[i]) {
                    future_index[i][j] = k;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < MAX_PAGES; i++) {
        int page_number = reference_string[i];
        int page_found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (page_frames[j] == page_number) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            page_faults++;
            int max_future_index = -1;
            int replace_index = -1;

            for (int j = 0; j < MAX_FRAMES; j++) {
                if (future_index[j][i] > max_future_index) {
                    max_future_index = future_index[j][i];
                    replace_index = j;
                }
            }

            page_frames[replace_index] = page_number;
        }

        printf("Page Frames: ");
        for (int j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", page_frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
