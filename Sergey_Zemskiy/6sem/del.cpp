void Merge(long arr[], long aux[], int low, int mid, int high)
{
    int k = low, i = low, j = mid + 1;


    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j] ) {
            aux[k++] = arr[i++];
        }
        else {
            aux[k++] = arr[j++];
        }
    }


    while (i <= mid) {
        aux[k++] = arr[i++];
    }





    for (int i = low; i < high; i++) {
        arr[i] = aux[i];
    }
}
