#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int main() {
    int reference_string[MAX_PAGES];
    int page_frames[MAX_FRAMES];
    int page_faults = 0;
    int frame_pointer = 0;

    printf("Enter the reference string (sequence of page numbers): ");
    for (int i = 0; i < MAX_PAGES; i++) {
        scanf("%d", &reference_string[i]);
    }

    for (int i = 0; i < MAX_FRAMES; i++) {
        page_frames[i] = -1;
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
            page_frames[frame_pointer] = page_number;
            frame_pointer = (frame_pointer + 1) % MAX_FRAMES;
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
