! NAME: MANEESH WIJEWARDHANA
! ID: 1125828
! COURSE: CIS*3190
! DUE DATE: FEB 3
! This file contains the main subroutines to solve anagrams as well as extra helper subroutines
! Algorithm used to generate permutations of strings are cited above the functionality

program main
   ! modules, structures, and variables
   use lexicon
   implicit none

   type :: jumblePair
      character(len=40) :: jumble
      character(len=40) :: realAnagram
   end type

   type(jumblePair), allocatable :: jPair(:)
   type(jumblePair), allocatable :: finalJPair(:)

   character*40, allocatable :: wordArr(:)
   character*256, allocatable :: dictionary(:)
   character(len=3) :: isSolve
   character(len=32):: charsInEachJumble
   character(len=32):: finalJumble = ""

   integer :: n, leftSide = 1, count, found = 0, dictSize, low, high

   ! this will fill our dict array with all the words from dict of words provided (only do it once)
   call buildlexicon(dictionary)

   dictSize = size(dictionary)
   ! since the dict is not ascii sorted but alphabetically, we will toLower it in order to perform a more effecient search later on
   do n = 1, dictSize
      call toLowerCase(dictionary(n))
   end do

   ! prompt the user for # of words and return an array of words
   call inputJumble(wordArr)

   ! need to allocate enough keyvalue pairs in dictionary
   allocate (jPair(size(wordArr)))

   ! generate all possible anagrams for each individual word inside array and store in anagram array in dict
   do n = 1, size(wordArr)
      call toLowerCase(wordArr(n)) ! make sure capitals work the same
      found = 0
      count = 1
      jPair(n)%jumble = wordArr(n)

      call generateAnagram(dictionary, wordArr(n), leftSide, jPair(n)%realAnagram, count, found, low, high)

      if (found == 0) then
         jPair(n)%realAnagram = 'No real anagram found'
      end if
   end do

   write (*, '(a)') ''
   write (*, '(a)') 'The following jumbles have been solved:'

   do n = 1, size(jPair)
      write (*, *) trim(jPair(n)%jumble), ': ', trim(jPair(n)%realAnagram)
   end do

   write (*, '(a)') ''
   write (*, '(a)') 'Solve word jumble puzzle? (Y/N)'
   read (*, *) isSolve

   call toLowerCase(isSolve)

   if (isSolve == 'y' .or. isSolve == 'yes') then
      ! reset variables from first generateAnagram
      found = 0
      count = 0
      leftSide = 1

      write (*, '(a)') ''
      write (*, '(a)') 'Select circled letters from word puzzle: (Enter letters followed by RETURN key to move to the next jumble)'
      ! We will keep concatenating the chars to a variable for each user input
      do n = 1, size(wordArr)
         write (*, *) wordArr(n)
         read (*, '(a)') charsInEachJumble
         finalJumble = trim(finalJumble)//trim(charsInEachJumble)
      end do

      ! handle the case where the user has inconsistent spacing and uppercases when entering chars
      call stripSpaces(finalJumble)
      call toLowerCase(finalJumble)

      ! we only need to allocate one for this since it will always be one final jumble
      allocate (finalJPair(1))
      finalJPair(1)%jumble = trim(finalJumble)

      write (*, *) 'Jumbled word: ', finalJPair(1)%jumble
      write (*, '(a)') ''

      call generateAnagram(dictionary, finalJPair(1)%jumble, leftSide, finalJPair(1)%realAnagram, count, found, low, high)

      write (*, *) 'Solved jumble: ', finalJPair(1)%realAnagram
   else
      return
   end if
   deallocate (jPair)
   deallocate (finalJPair)

contains
   subroutine inputJumble(wordArray)
      implicit none
      character*40, allocatable, intent(inout) :: wordArray(:)
      integer :: i, wordCount, ierror

      write (*, *) 'How many jumbled words?'
      read (*, '(i10)', iostat=ierror) wordCount
      if (ierror == 0) then
         allocate (wordArray(wordCount))
      else
         write (*, *) 'Error: Please enter an integer'
         return
      end if

      write (*, '(a)', advance='no') 'Enter the '
      write (*, '(I0)', advance='no') wordCount
      write (*, '(a)') ' jumbled words'

      do i = 1, wordCount
         read (*, *) wordArray(i)
      end do
   end subroutine inputJumble

   ! takes in each string in jumbled array then returns all permuations using a recursive approach
   recursive subroutine generateAnagram(dict, str, l, realAnagram, j, bool, lowIdx, highIdx)
      implicit none
      character*256, allocatable, intent(inout) :: dict(:)
      character(len=*), intent(inout) :: str
      character(len=40), intent(inout) :: realAnagram
      integer, intent(in) :: l
      integer :: i
      integer, intent(inout) :: j, bool, lowIdx, highIdx

      ! after each anagram is found we make sure it is a real word before saving. We know it is a real word if bool == 1 based on findlex
      ! recursive permutation algorithm referenced from https://craftofcoding.wordpress.com/2023/01/23/recursion-permutations-by-interchange/

      if (l == len_trim(str) .and. bool == 0) then
         call findAnagram(dict, lowIdx, highIdx, str, realAnagram, bool)
         j = j + 1
      else
         do i = l, len_trim(str)
            call swap(str(l:l), str(i:i))
            call generateAnagram(dict, str, l + 1, realAnagram, j, bool, lowIdx, highIdx)
            call swap(str(l:l), str(i:i)) ! backtracking
         end do
      end if
   end subroutine generateAnagram

   subroutine findAnagram(dict, lowIdx, highIdx, str, realAnagram, bool)
      implicit none
      character*256, allocatable, intent(inout) :: dict(:)
      character(len=40), intent(inout) :: realAnagram
      character(len=40), intent(inout) :: str
      integer, intent(inout):: lowIdx, highIdx, bool

      call findlex(dict, lowIdx, highIdx, str, bool)

      if (bool == 1) then
         realAnagram = str
         return
      end if
   end subroutine findAnagram

   ! Helper subroutine to swap two characters
   subroutine swap(a, b)
      implicit none
      character(len=1), intent(inout) :: a, b
      character(len=1) :: temp
      temp = a
      a = b
      b = temp
   end subroutine swap

   ! Helper subrouutine to stip spaces in between chars
   subroutine stripSpaces(string)
      implicit none
      character(len=*) :: string
      integer :: stringLen
      integer :: last, actual

      stringLen = len(string)
      last = 1
      actual = 1

      do while (actual < stringLen)
         if (string(last:last) == ' ') then
            actual = actual + 1
            string(last:last) = string(actual:actual)
            string(actual:actual) = ' '
         else
            last = last + 1
            if (actual < last) then
               actual = last
            end if
         end if
      end do
   end subroutine

   ! Helper subroutine to lowercase a string
   subroutine toLowerCase(string)
      implicit none
      character(*), intent(inout) :: string
      character(26) :: capital = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
      character(26) :: lowercase = 'abcdefghijklmnopqrstuvwxyz'
      integer :: curr, i

      ! lowercase each letter if it is uppercase
      do i = 1, len_trim(string)
         curr = index(capital, string(i:i))
         if (curr > 0) then
            string(i:i) = lowercase(curr:curr)
         end if
      end do
   end subroutine toLowerCase
end program main
