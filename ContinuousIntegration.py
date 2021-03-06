#!/usr/bin/python2.7
import git
import os
from subprocess import Popen, PIPE

################################################################################
def BuildAndUpload(ProjectFilePath):
  os.chdir(ProjectFilePath)
  print Popen([r"ino","build"], stdout=PIPE).communicate()[0]
  print Popen([r"ino", "upload"], stdout=PIPE).communicate()[0]

################################################################################
def Update(RepoFilePath, BranchName):
  repo = git.Repo(RepoFilePath)
  repo.git.checkout(BranchName)

  OldHash = repo.head.commit.hexsha[0:7]
  repo.git.pull()

  #update any submodules
  for SubModule in repo.submodules:
    SubRepo = git.Repo(RepoFilePath + os.sep + SubModule.path)
    repo.git.checkout(BranchName)
    repo.git.pull()

  NewHash = repo.head.commit.hexsha[0:7]
  return (NewHash is not OldHash), NewHash, OldHash

################################################################################
################################################################################
if __name__ == "__main__":
  RepoPath = os.path.expanduser('~/PartyMode')
  if Update(RepoPath, 'master'):
    BuildAndUpload(RepoPath + '/MainPanel')
