C Make Fortran CLOSE available to C/C++
      subroutine ftnclose( unit )
      implicit none
      integer unit
      close( unit )
      return
      end
