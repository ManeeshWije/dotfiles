! NAME: MANEESH WIJEWARDHANA
! ID: 1125828
! COURSE: CIS*3190
! DUE DATE: APRIL 7
! This file contains the main program to read in a file of integers and the dobosort subroutine

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
   call doboSort(intArr, count)
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
   ! this subroutine finds the next gap from current
   subroutine getNextGap(gap)
      integer, intent(inout) :: gap

      ! shrink gap by shrink factor
      gap = int((gap*10)/13)
      if (gap < 1) then
         gap = 1
      end if
   end subroutine getNextGap

   ! this subroutine will sort the array using comb sort
   subroutine doboSort(integers, c)
      integer, dimension(:), allocatable, intent(inout) :: integers
      integer, intent(in) :: c
      integer :: gap, idx
      logical :: swapped

      ! init gap
      gap = c
      ! swap to true to make sure loop runs
      swapped = .true.

      ! keep running while gap is more than 1 and last iteration caused a swap
      do while (gap /= 1 .or. swapped .eqv. .true.)
         ! find next gap
         call getNextGap(gap)
         ! swap to false so we can check if swap happened or not
         swapped = .false.
         ! now compare with curr gap
         do idx = 1, c - gap
            if (integers(idx) > integers(idx + gap)) then
               call swap(integers(idx), integers(idx + gap))
               swapped = .true.
            end if
         end do
      end do
   end subroutine doboSort

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
