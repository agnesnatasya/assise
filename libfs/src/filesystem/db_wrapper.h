#ifndef TABLE_FS_H
#define TABLE_FS_H


class DBWrapper {
public:
  ~DBWrapper() {
  }

  void SetState(FileSystemState* state);

  void* Init(struct fuse_conn_info *conn);

  void Destroy(void * data);

  int GetAttr(const char *path, struct stat *statbuf);

  void Compact();

  bool GetStat(std::string stat, std::string* value);

private:
  FileSystemState *state_;
  LevelDBAdaptor* metadb;

  inline int FSError(const char *error_message);

  inline void DeleteDBFile(tfs_inode_t inode_id, int filesize);

  inline void GetDiskFilePath(char *path, tfs_inode_t inode_id);

  inline int OpenDiskFile(const tfs_inode_header* iheader, int flags);

  inline int TruncateDiskFile(tfs_inode_t inode_id, off_t new_size);

  inline ssize_t MigrateDiskFileToBuffer(tfs_inode_t inode_it,
                                         char* buffer, size_t size);

  int MigrateToDiskFile(InodeCacheHandle* handle, int &fd, int flags);

  inline void CloseDiskFile(int& fd_);

  inline void InitStat(struct stat &statbuf,
                       tfs_inode_t inode,
                       mode_t mode,
                       dev_t dev);

  tfs_inode_val_t InitInodeValue(tfs_inode_t inum,
                                 mode_t mode,
                                 dev_t dev,
                                 leveldb::Slice filename);

  std::string InitInodeValue(const std::string& old_value,
                             leveldb::Slice filename);

  void FreeInodeValue(tfs_inode_val_t &ival);

  bool ParentPathLookup(const char* path,
                        tfs_meta_key_t &key,
                        tfs_inode_t &inode_in_search,
                        const char* &lastdelimiter);

  inline bool PathLookup(const char *path,
                         tfs_meta_key_t &key,
                         leveldb::Slice &filename);

  inline bool PathLookup(const char *path,
                         tfs_meta_key_t &key);

};

#endif
