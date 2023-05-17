void Merge(long arr[], long aux[], int low, int mid, int high)
{
	int k = low, i = low, j = mid + 1;

	// while there are elements in the left and right runs
	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j]) {
			aux[k++] = arr[i++];
		}
		else {
			aux[k++] = arr[j++];
		}
	}

	// copy remaining elements
	while (i <= mid) {
		aux[k++] = arr[i++];
	}

	// No need to copy the second half (since the remaining items
	// are already in their correct position in the auxiliary array)

	// copy back to the original array to reflect sorted order
	for (int i = low; i <= high; i++) {
		arr[i] = aux[i];
	}
}
