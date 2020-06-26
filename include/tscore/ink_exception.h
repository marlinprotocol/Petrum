#pragma once

class Exception
{
};

class OSException : public Exception
{
};

class IOException : public OSException
{
};

class FileOpenException : public IOException
{
};
class FileStatException : public IOException
{
};
class FileSeekException : public IOException
{
};
class FileReadException : public IOException
{
};
class FileWriteException : public IOException
{
};
class FileCloseException : public IOException
{
};

class MemoryMapException : public OSException
{
};
class MemoryUnmapException : public OSException
{
};
