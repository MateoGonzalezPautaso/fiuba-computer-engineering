import subprocess
import pytest

@pytest.mark.describe('FFT')
class TestFFT():
    @pytest.mark.it('1024 4 way 32 sets summary')
    def test_fft_1024_4_32_summary(self):
        args = ['./cachesim','./trazas/FFT.xex','1024','4','32']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/fft_1024-4-32_summary.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout

    @pytest.mark.it('1024 4 way 32 sets')
    def test_fft_1024_4_32(self):
        args = ['./cachesim','./trazas/FFT.xex','1024','4','32','-v','0','15000']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/fft_1024-4-32.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout

    @pytest.mark.it('8192 direct-mapped')
    def test_fft_8192(self):
        args = ['./cachesim','./trazas/FFT.xex','8192','1','256','-v','0','10000']

        result = subprocess.run(args, capture_output=True, text=True)
        exit_code = result.returncode

        assert exit_code == 0

        stdout = result.stdout.splitlines()
        data = ''
        with open('./output/fft_8192-1-256.txt','r') as f:
            data = f.read().splitlines()
        
        for line_data, line_stdout in zip(data,stdout):
            assert line_data == line_stdout