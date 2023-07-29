! NAME: MANEESH WIJEWARDHANA
! ID: 1125828
! COURSE: CIS*3190
! DUE DATE: APRIL 7
! This file contains the main program to read in a file of integers and the bubblesort subroutine

program main
   implicit none
   integer :: i, n, count
   integer, dimension(:), allocatable :: intArr, intTemp
   real :: T1, T2
   character(len=20) :: filename

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
   call bubbleSort(intArr, count)
   call cpu_time(T2)
   print *, "Elapsed time: ", (T2 - T1)*1000, "ms"
   write (*, *) "sortedF.txt has been created"

contains
   subroutine bubbleSort(integers, c)
      implicit none
      integer, dimension(:), intent(inout) :: integers
      integer :: j, k, temp, l
      integer, intent(in) :: c

      do j = count - 1, 1, -1
         do k = 1, j
            if (integers(k) > integers(k + 1)) then
               temp = integers(k)
               integers(k) = integers(k + 1)
               integers(k + 1) = temp
            end if
         end do
      end do

      ! output data into a file
      open (1, file='sortedF.txt', status='unknown')
      do l = 1, c
         write (1, *) integers(l)
      end do
      close (1)
   end subroutine bubbleSort
end program main
