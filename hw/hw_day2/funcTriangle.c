void ex1(char ch, int size){
        int rows, cols;

        for(rows = 1; rows < size+1; rows++) {
                for(cols=rows; cols < size+1; cols++) {
                        printf("%c", ch);
                }
                printf("\n");
        }
}

void ex2(char ch, int size){
        int rows, cols;

        for(rows = size+1; rows >= 1; rows--) {
                for(cols=rows; cols < size+1; cols++) {
                        printf("%c", ch);
                }
                printf("\n");
        }
}

void ex3(char ch, int size){
        int rows, cols;

        for(rows = size+1; rows >= 1; rows--) {
                for(cols=rows; cols < size+1; cols++) {
                        printf("%c", ch);
                }
                printf("\n");
        }

        for(rows = 1; rows < size+1; rows++) {
                for(cols=rows; cols < size; cols++) {
                        printf("%c", ch);
                }
                printf("\n");
        }
}

void ex4(char ch, int size){
        int rows, cols, spaceCounter=-1;
        int counter;
        for (rows = 0; rows <= size-1; rows++) {
                spaceCounter++;
                counter = spaceCounter;
                while(counter != 0) {
                        printf(" ");
                        counter--;
                }
                for (cols = rows; cols <= size-1; cols++) {
                        printf("%c ", ch);
                }
                printf("\n");
        }
}

void ex5(char ch, int size){
        int rows, cols, spaceCounter=size;
        int counter;
        for (rows = size; rows >= 0; rows--) {
                spaceCounter--;
                counter = spaceCounter;
                while(counter >= 0) {
                        printf(" ");
                        counter--;
                }
                for (cols = rows; cols <= size-1; cols++) {
                        printf("%c ", ch);
                }
                printf("\n");
        }
}

void ex6(char ch, int size){
        int rows, cols, spaceCounter=size;
        int counter;
        for (rows = size; rows > 0; rows--) {
                spaceCounter--;
                counter = spaceCounter;
                while(counter >= 0) {
                        printf(" ");
                        counter--;
                }
                for (cols = rows; cols <= size-1; cols++) {
                        printf("%c ", ch);
                }
                printf("\n");
        }

        spaceCounter=-1;
        for (rows = 0; rows <= size-1; rows++) {
                spaceCounter++;
                counter = spaceCounter;
                while(counter != 0) {
                        printf(" ");
                        counter--;
                }
                for (cols = rows; cols <= size-1; cols++) {
                        printf("%c ",ch);
                }
                printf("\n");
        }
}
