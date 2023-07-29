def s():
    nums=[1, 22, 99, 2, 4, 3]
    v=0
    j=0
    for i in range(1,len(nums)):
        v=nums[i]
        j=i-1
        while j>=0 and nums[j]>v:
            nums[j+1]=nums[j]
        j=j-1
        nums[j+1]=v
    return nums
