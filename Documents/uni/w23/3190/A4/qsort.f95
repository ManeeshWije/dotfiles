! NAME: MANEESH WIJEWARDHANA
! ID: 1125828
! COURSE: CIS*3190
! DUE DATE: APRIL 7
! This file contains the main program to read in a file of integers and the quicksort subroutine

program main
   implicit none
   integer :: i, n, count, l
   integer, dimension(:), allocatable :: intArr, intTemp
   character(len=20) :: filename
   real :: T1, T2

   write (*, *) "Enter the name of the input file: "
   read (*, *) filename

   open (unit=10, file=filename, status='old', action='read')

   ! initial size of array
   n = 1000
   allocate (intArr(n))

   ! count to keep track if we need to allocate more space
   count = 0

   do
      read (10, *, iostat=i) intArr(count + 1)
      if (i /= 0) then
         exit
      end if
      count = count + 1

      ! check if full
      if (count == n) then
         n = n*2
         ! use temp array to make sure we dont allocate allocated array again
         allocate (intTemp(n))
         intTemp(1:count) = intArr(1:count)
         deallocate (intArr)
         allocate (intArr(n))
         intArr(1:count) = intTemp(1:count)
         deallocate (intTemp)
      end if
   end do
   close (unit=10)

   call cpu_time(T1)
   call quickSort(intArr, 1, count)
   call cpu_time(T2)

   ! output data into a file
   open (1, file='sortedF.txt', status='unknown')
   do l = 1, count
      write (1, *) intArr(l)
   end do
   close (1)
   print *, "Elapsed time: ", (T2 - T1)*1000, "ms"
   write (*, *) "sortedF.txt has been created"

contains
   subroutine partition(integers, low, high, res)
      implicit none
      integer, dimension(:), intent(inout) :: integers
      integer, intent(in) :: low, high
      integer, intent(inout) :: res
      integer :: pivot, j, idxx

      ! choose rightmost element as pivot
      pivot = integers(high)
      ! pointer for greater element
      idxx = low - 1

      ! traverse through and compare with pivot
      do j = low, high
         ! if smaller than pivot, swap with greater element pointed by idx
         if (integers(j) < pivot) then
            idxx = idxx + 1
            call swap(integers(idxx), integers(j))
         end if
      end do
      ! swap pivot element with greater element pointed by idx
      call swap(integers(idxx + 1), integers(high))

      ! return the position from where the partition is done
      res = idxx + 1
   end subroutine partition

   recursive subroutine quickSort(integers, low, high)
      implicit none
      integer, dimension(:), intent(inout) :: integers
      integer, intent(in) :: low, high
      integer :: result

      if (low < high) then
         ! find pivot such that element smaller are on left and element greater are on right
         call partition(integers, low, high, result)
         call quickSort(integers, low, result - 1)
         call quickSort(integers, result + 1, high)
      end if
   end subroutine quickSort

   ! Helper subroutine to swap two integers
   subroutine swap(a, b)
      implicit none
      integer, intent(inout) :: a, b
      integer :: temp
      temp = a
      a = b
      b = temp
   end subroutine swap
end program main
