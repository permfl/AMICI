import numpy as np
import scipy as sp
import h5py


class DataProvider:

    def __init__(self, h5_file):
        self.h5_file = h5_file

    def get_edata():
        pass

    def get_timepoints():
        pass

    def get_pscales():
        pass

    def get_fixed_parameters():
        pass

    def get_initial_states():
        pass
    
    @staticmethod
    def convert_benchmark_to_h5(model_name):
        """
        Convert the data format in the benchmark study by Loos et al. to
        hdf5.

        Parameters
        ----------

        model: str
            e.g. "Fujita_SciSignal2010", file name relative to current
            working directory

        Returns
        -------

        dp: DataProvider
            a DataProvider to the generated h5_file
        """

        # check if h5 file exists already, then error

        # observables

        # fixed parameters

        # timepoints

        # ...
