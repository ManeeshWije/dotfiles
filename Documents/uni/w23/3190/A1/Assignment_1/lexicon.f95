! NAME: MANEESH WIJEWARDHANA
! ID: 1125828
! COURSE: CIS*3190
! DUE DATE: FEB 3
! This file contains the lexicon subroutines that the main subroutines will take advantage of as well as some helper subroutines

module lexicon
   implicit none
contains
   ! reads system dict file and adds them to an array to use later
   subroutine buildlexicon(dictionary)
      implicit none
      character*256, allocatable, intent(out) :: dictionary(:)
      integer :: i, lineCount = 0, io
      ! open existing file and count num lines in order to allocate array
      open (1, file='dict2.txt', status='old')
      do
         read (1, *, iostat=io)
         if (io /= 0) then
            exit
         else
            lineCount = lineCount + 1
         end if
      end do

      allocate (dictionary(lineCount))

      rewind (1) ! reset the file to original point
      ! read words into array
      do i = 1, size(dictionary)
         read (1, *) dictionary(i)
      end do
      close (1)
   end subroutine buildlexicon

   ! returns 1 if string exists in dictionary, 0 otherwise
   subroutine findlex(dictionary, low, high, s, bool)
      implicit none
      character*256, allocatable, intent(inout) :: dictionary(:)
      character(len=*), intent(inout) :: s
      integer, intent(inout) :: bool, low, high
      integer :: mid

      low = 1
      high = size(dictionary)

      ! because our dictionary of words are sorted, we will binary search to increase speed
      do while (low <= high)
         mid = (low + high)/2
         if (dictionary(mid) == s) then
            bool = 1
            exit
         else if (dictionary(mid) < s) then
            low = mid + 1
         else
            high = mid - 1
         end if
      end do
   end subroutine findlex
end module lexicon
