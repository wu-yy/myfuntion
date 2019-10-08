void QuickSort(vector<int>& input , int begin1, int end1) {
    int number =  input[end1];
    int index = end1;
    cout << "begin:" << begin1 << " end: " << end1 << endl;
    for (auto& p : input) {
      cout << p << " ";
    }
    cout <<endl;
    for (int i =begin1; i < end1; i++) {
      if (input[i] > number) {
        input[end1] = input[i];
        index = i;
        input[index] = number;
        break;
      }
    }

    for (int i =  index; i < end1; i++) {
      if (input[i] < number) {
        int tmp = input[index];
        input[index] = input[i];
        index++;
        input[i] = tmp;
      }
    }
    if (begin1 < index - 1) {
      QuickSort(input, begin1,  index-1);
    }
    if (index < end1) {
      QuickSort(input, index, end1);
    }
  }
